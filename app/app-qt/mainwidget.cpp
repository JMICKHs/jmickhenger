#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "chatinput.h"
#include <QDebug>
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    menuWidget = new MenuWidget(this);
    chatModel = new ChatModel(this);
    groupModel = new GroupModel(this);

    proxyModel = new ProxyModel(this);
    proxyModel->setSourceModel(groupModel);
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

    Chat item1;
    item1.idChat = 3;
    item1.name = "Textopark algosi";
    //item1.idUsers = {3,2,1};
    //item1.lastMessage = "skinyte semenar";
    //Chat
    //item1. = "23:44";
    for(int i = 0 ; i < 23; ++i){
        groupModel->addItem(item1);

        item1.name = std::to_string(i);
    }
    chatModel = new ChatModel();
    ui->chatList->setModel(chatModel);
    ui->chatList->setItemDelegate(new ChatDelegate);
    ui->chatList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->chatList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
    delete chatModel;
    delete groupModel;
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    menuWidget->resize(0,event->size().height());
}

void MainWidget::moveEvent(QMoveEvent *event)
{
    menuWidget->move(event->pos());
}

void MainWidget::menuClicked()
{
    menuWidget->move(QPoint(geometry().x(),geometry().y()));
    emit menuWidget->setPosition();
}

void MainWidget::sendMessageFromInput()
{

    Message message;
    QString text = ui->messageInput->toPlainText().trimmed();
    removeDoubleEnter(text);
    message.text = text.toStdString();

    qDebug() << QString::fromStdString(message.text);
    //message.name = "kostya";
    message.timesend  = 0;
    chatModel->createMessage(message);
    ui->messageInput->clear();
    auto net = AppNetwork::shared();

    net->sendMessage(message,[](const bool&,std::optional<string>&){});
    emit ui->chatList->doItemsLayout();
}

void MainWidget::on_groupList_clicked(const QModelIndex &index)
{
    ui->label->setText(QString::fromStdString(index.model()->data(index).value<Chat>().name));
  //  QString info = QString::number(index.model()->data(index).value<Chat>().idUsers.size());
    //if(info <= 2)
    //    info += "  участника";
    //else
    //    info += "  участников";
    //
    //ui->label_2->setText(info);
}

void MainWidget::on_searchInput_textChanged(const QString &arg1)
{
    //proxyModel->setDynamicSortFilter(true);
    //proxyModel->setDynamicSortFilter(false);
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

