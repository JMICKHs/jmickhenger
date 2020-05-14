#include "app-qt/src/mainwidget/mainwidget.h"


#include "app-qt/src/models/chatmodel.h"
#include "app-qt/src/chatinput/chatinput.h"
#include "netlib/AppNetwork.h"
#include "ui_mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{

    ui->setupUi(this);

    menuWidget = new MenuWidget(this);
    msgMenu = new QMenu(this);
    chatModel = std::make_shared<ChatModel>();
    groupModel = std::make_shared<GroupModel>();
    groupModel->addCallbacks();
    chatModel->addCallbacks();

    proxyModel = new ProxyModel(this);
    proxyModel->setSourceModel(groupModel.get());
    ui->groupList->setModel(proxyModel);
    ui->groupList->setItemDelegate(new GroupDelegate);
    ui->groupList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->searchInput->setWindowFlag(Qt::FramelessWindowHint);
    ui->messageInput->setWindowFlag(Qt::FramelessWindowHint);

    QPalette linesPallet(palette());
    linesPallet.setColor(QPalette::Light,QColor(230,230,230));
    ui->line->setPalette(linesPallet);
    ui->line_4->setPalette(linesPallet);
    ui->line_2->setPalette(linesPallet);
    ui->line_3->setPalette(linesPallet);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    auto font =  ui->label->font();
    font.setBold(true);
    ui->label->setFont(font);
    ui->chatList->setModel(chatModel.get());
    ui->chatList->setItemDelegate(new ChatDelegate);
    ui->chatList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->chatList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    QAction * editDevice = new QAction("Редактировать", this);
    QAction * deleteDevice = new QAction("Удалить", this);

    connect(editDevice, &QAction::triggered, this, &MainWidget::editMessageInChat);
    connect(deleteDevice, &QAction::triggered, this, &MainWidget::removeMessageFromChat);

    msgMenu->addAction(editDevice);
    msgMenu->addAction(deleteDevice);
    ui->chatList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->chatList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->chatList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->chatList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(menuWidget->getCreateWidget(),&CreateGroupWidget::groupCreated,groupModel.get(),&GroupModel::createChatByUser);
    connect(ui->chatList,&ChatView::customContextMenuRequested,this,&MainWidget::showContextMenu);
    connect(ui->menuButton,&CustomButton::clicked,menuWidget,&MenuWidget::show);
    connect(ui->menuButton,&CustomButton::clicked,this,&MainWidget::menuClicked);
    connect(ui->sendButton,&CustomButton::clicked,this,&MainWidget::sendMessageFromInput);
    connect(ui->searchInput,&QLineEdit::textChanged,proxyModel,&ProxyModel::search_String_Changed);
    connect(ui->messageInput,&ChatInput::sendMessageOnEnter,this,&MainWidget::sendMessageFromInput);
    this->setLayout(ui->MainLayout);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete menuWidget;

}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    menuWidget->resize(0,event->size().height());
}

void MainWidget::moveEvent(QMoveEvent *event)
{
    menuWidget->move(event->pos());
}

void MainWidget::wheelEvent(QWheelEvent *event)
{
    ui->chatList->doItemsLayout();
}

void MainWidget::menuClicked()
{
    menuWidget->move(QPoint(geometry().x(),geometry().y()));
    emit menuWidget->setPosition();
}

void MainWidget::sendMessageFromInput()
{

    Msg message;
    QString text = ui->messageInput->toPlainText().trimmed();
    if(text.size() > 1024)
        return;
    removeDoubleEnter(text);
    message.chatId = ui->chatList->selectionModel()->currentIndex().data().value<Chat>().idChat;
    message.text = text.toStdString();
    message.nickname = QString::fromStdString(UserModel::instance()->getAcc().login);
    message.idOwner = UserModel::instance()->getId();
    message.timesend  = 0;

    chatModel->createMessage(message);
    ui->messageInput->clear();
    auto net = AppNet::shared();
    net->sendMsg(message,[](std::optional<string>&){});
    emit ui->chatList->doItemsLayout();
}

void MainWidget::on_groupList_clicked(const QModelIndex &index)
{
    ui->label->setText(QString::fromStdString(index.model()->data(index).value<Chat>().name));
    auto net = AppNet::shared();
    Chat chat = index.model()->data(index).value<Chat>();
    net->getMsgs(chat.idChat,0,50,chatModel->getChatCallback());
    ui->chatList->doItemsLayout();
    ui->chatList->update();

    //QString info = QString::number(index.model()->data(index).value<Chat>().);
    //if(info <= 2)
    //    info += "  участника";
    //else
    //    info += "  участников";
    //
    //ui->label_2->setText(info);
}


void MainWidget::after_Login_slot()
{
    this->show();
    Account ac = UserModel::instance()->getAcc();
    auto net = AppNet::shared();
    net->getListChat(ac.id,groupModel->getChatCallBack());
    menuWidget->setName(QString::fromStdString(ac.login));
    connect(UserModel::instance(),&UserModel::nickNameChanged,menuWidget,&MenuWidget::on_nickname_rename);
}

void MainWidget::removeMessageFromChat()
{
    Msg msg = ui->chatList->selectionModel()->currentIndex().data().value<Msg>();
    if(msg.idOwner == UserModel::instance()->getId()){
        chatModel->DeleteMessage(ui->chatList->selectionModel()->currentIndex().row());
    }
    else{

    }
    ui->chatList->doItemsLayout();
}

void MainWidget::editMessageInChat()
{

}

void MainWidget::showContextMenu(const QPoint &pos)
{
    msgMenu->popup(ui->chatList->viewport()->mapToGlobal(pos));
}

void MainWidget::removeDoubleEnter(QString &str){

    int counter = 0;
    int pos = 0;
    for(int i = 0; i < str.size(); ++i){
        if(str[i] == '\n'){
            pos = i;
            counter++;
            ++i;
            while(str[i] == '\n'){
                counter++;
                ++i;
            }
        }
        else
            counter = 0;
        if(counter > 1){
            str.remove(pos + 1,counter - 1);
        }
    }
}

