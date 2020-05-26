#include "app-qt/src/mainwidget/mainwidget.h"
#include "app-qt/src/models/chatmodel.h"
#include "app-qt/src/chatinput/chatinput.h"
#include "netlib/AppNetwork.h"
#include "netlib/info/Info.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtWebView/QtWebView>

#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    qRegisterMetaType<inf::ChatRoom>();
    qRegisterMetaType<std::vector<MessageItem>>();
    ui->setupUi(this);
    this->setFocusPolicy(Qt::WheelFocus);
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

    chatDelegate = new ChatDelegate(this);
    ui->chatList->setItemDelegate(chatDelegate);

    QAction * editDevice = new QAction("Редактировать", this);
    QAction * deleteDevice = new QAction("Удалить", this);
    QAction * copyDevice = new QAction("Скопировать",this);

    connect(editDevice, &QAction::triggered, this, &MainWidget::editMessageInChat);
    connect(deleteDevice, &QAction::triggered, this, &MainWidget::removeMessageFromChat);
    connect(copyDevice,&QAction::triggered,this,&MainWidget::copyMessage);

    msgMenu->addAction(copyDevice);
    msgMenu->addAction(editDevice);
    msgMenu->addAction(deleteDevice);

    ui->chatList->setWindowFlag(Qt::FramelessWindowHint);
    ui->chatList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->chatList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->chatList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->chatList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(menuWidget->getCreateWidget(),&CreateGroupWidget::groupCreated,groupModel.get(),&GroupModel::createChatByUser);
    connect(ui->chatList,&ChatView::customContextMenuRequested,this,&MainWidget::showContextMenu);
    connect(ui->menuButton,&CustomButton::clicked,menuWidget,&MenuWidget::show);
    connect(ui->menuButton,&CustomButton::clicked,this,&MainWidget::menuClicked);
    connect(ui->sendButton,&CustomButton::clicked,this,&MainWidget::sendMessageFromInput);
    connect(ui->searchInput,&QLineEdit::textChanged,proxyModel,&ProxyModel::search_String_Changed);
    connect(ui->messageInput,&ChatInput::sendMessageOnEnter,this,&MainWidget::sendMessageFromInput);
    connect(chatModel.get(),&ChatModel::messageCreateByUser,groupModel.get(),&GroupModel::messageCreateByUser);
    connect(groupModel.get(),&GroupModel::sendChatRoom,this,&MainWidget::setGroupInfoSlot);
    connect(this,&MainWidget::sendAvatar,menuWidget,&MenuWidget::on_image_change);
    connect(groupModel.get(),&GroupModel::sendNewMessages,chatModel.get(),&ChatModel::newMessages);
    connect(groupModel.get(),&GroupModel::updateItems,ui->groupList,&GroupListView::doItemsLayout);
    connect(chatModel.get(),&ChatModel::updateItems,ui->chatList,&ChatView::doItemsLayout);
    connect(ui->chatList,&ChatView::insertRow,this,&MainWidget::resizeSpacer);
    AppNet::shared()->setObserverUnknownChat(groupModel->getUnknownChatRoomAdd());
    connect(groupModel.get(),&GroupModel::messageChecked,chatModel.get(),&ChatModel::msgsChecked);
    connect(chatModel.get(),&ChatModel::setLastMessageInGroup,groupModel.get(),&GroupModel::setLastMessage);
    connect(this,&MainWidget::setTextForChange,ui->messageInput,&ChatInput::textForChange);
    connect(groupModel.get(),&GroupModel::deleteMsg,chatModel.get(),&ChatModel::DeleteMessage);
    connect(ui->messageInput,&ChatInput::sendMessageForChange,this,&MainWidget::messageEdited);
    connect(ui->messageInput,&ChatInput::changeSpacer,this,&MainWidget::resizeSpacer);
    this->setLayout(ui->MainLayout);
    ui->menuButton->setIcon(QIcon(":/img/menu.jpg"));
    spacerHeight = ui->offsetSpacer->maximumSize().height();
    ui->chatList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

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


MenuWidget *MainWidget::getMenu()
{
    return menuWidget;
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
    if(text == "" && !ui->messageInput->created)
        return;
    if(text.size() > 1024)
        return;
    removeDoubleEnter(text);
    message.chatId = ui->groupList->selectionModel()->currentIndex().data().value<Chat>().idChat;
    message.text = text.toStdString();
    message.nickname = QString::fromStdString(UserModel::instance()->getAcc().login);
    message.idOwner = UserModel::instance()->getId();
    message.avatar = QString::fromStdString(UserModel::instance()->getAcc().avatar);

    long int ttime;
    ttime = time(NULL);
    char buffer [100];
    tm* timeinfo = localtime(&ttime);
    strftime(buffer,100,"%H-%M",timeinfo);
    message.time = QString::fromStdString(std::string(buffer));
    message.type = MessageType::SELF_MESSAGE_IN_PROGRESS;
    message.timesend  = ttime;

    QString str = "";
    std::optional<QPixmap> map;
    if(ui->messageInput->created){
        map.emplace(ui->messageInput->image);
        ui->messageInput->created = false;
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        map.value().save(&buffer, "jpg");
        str = QString(bytes.toBase64());
        QByteArray buf2 = QByteArray::fromBase64(str.toLocal8Bit());
        QPixmap mp;
        mp.loadFromData(buf2);
        map.value() = mp;
    }
    message.image = str.toStdString();
    chatModel->createMessage(message,map);
    emit chatModel->messageCreateByUser(message);
    ui->messageInput->clear();
    auto net = AppNet::shared();
    net->sendMsg(message,chatModel->getSendMsgCallback());
    emit ui->chatList->doItemsLayout();
    emit ui->groupList->doItemsLayout();
}

void MainWidget::on_groupList_clicked(const QModelIndex &index)
{
    ui->label->setText(QString::fromStdString(index.model()->data(index).value<Chat>().name));
    ui->offsetSpacer->changeSize(0,spacerHeight,QSizePolicy::Fixed,QSizePolicy::Fixed);
    Chat chat = index.model()->data(index).value<Chat>();
    if(groupModel->currChatId == chat.idChat)
        return;
    chatModel->Clear();
    groupModel->chatInfoSet(chat.idChat);
    groupModel->currChatId = chat.idChat;
    AppNet::shared()->getLastMsg(UserModel::instance()->getId(),chat.idChat,chatModel->getLastMsgAndGet());
}


void MainWidget::after_Login_slot()
{
    this->show();
    Account ac = UserModel::instance()->getAcc();
    AppNet::shared()->getListChat(ac.id,groupModel->getChatCallBack());
    menuWidget->setName(QString::fromStdString(ac.login));
    emit sendAvatar(QString::fromStdString(ac.avatar));
    connect(UserModel::instance(),&UserModel::nickNameChanged,menuWidget,&MenuWidget::on_nickname_rename);
}

void MainWidget::removeMessageFromChat()
{
    Msg msg = ui->chatList->selectionModel()->currentIndex().data().value<Msg>();
    chatModel->DeleteMessage(msg.number);
    int id = UserModel::instance()->getId();
    if(id == msg.idOwner){
        AppNet::shared()->dellMsg(UserModel::instance()->getId(),msg.chatId,msg.number,chatModel->getDelMsgCallback());
    }
    emit ui->chatList->doItemsLayout();
}

void MainWidget::editMessageInChat()
{
    Msg msg = ui->chatList->selectionModel()->currentIndex().data().value<Msg>();
    emit setTextForChange(QString::fromStdString(msg.text));
}

void MainWidget::messageEdited()
{
     Msg msg = ui->chatList->selectionModel()->currentIndex().data().value<Msg>();
     msg.text = ui->messageInput->toPlainText().toStdString();
     chatModel->changeMsg(msg);
     ui->messageInput->clear();
    // AppNet::shared()->changeMsg(UserModel::instance()->getId(),msg,[](std::optional<std::string> &){});
}

void MainWidget::showContextMenu(const QPoint &pos)
{
    msgMenu->popup(ui->chatList->viewport()->mapToGlobal(pos));
}

void MainWidget::setGroupInfoSlot(const inf::ChatRoom &room)
{
    QString info = QString::number(room.idUsers.size());
    if(room.idUsers.size() < 5)
        info += "  участника";
    else
        info += "  участников";

    ui->label_2->setText(info);
}

void MainWidget::resizeSpacer(int height)
{
    if( ui->offsetSpacer->maximumSize().height() - height <=0){
        ui->offsetSpacer->changeSize(0,0,QSizePolicy::Fixed,QSizePolicy::Fixed);
        return;
    }
    ui->offsetSpacer->changeSize(0,ui->offsetSpacer->maximumSize().height() - height,QSizePolicy::Fixed,QSizePolicy::Fixed);
}

void MainWidget::closeAll()
{
    AppNet::shared()->clearCache();
    AppNet::shared()->stopClient();
    this->close();
    AppNet::shared()->runClient(UserModel::instance()->getRunCallback());
}

void MainWidget::copyMessage()
{
    Msg msg = ui->chatList->selectionModel()->currentIndex().data().value<Msg>();
    QApplication::clipboard()->setText(QString::fromStdString(msg.text));
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
