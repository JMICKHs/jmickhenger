#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    menuWidget = new MenuWidget();
    chatModel = new ChatModel();
    groupModel = new GroupModel();

    ui->groupList->setModel(groupModel);
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

//    QPalette palette = ui->searchInput->palette();
//    palette.setColor(QPalette::Base,QColor(230,230,230));
//    ui->searchInput->setPalette(palette);

    GroupItem item1;
    item1.id = 3;
    item1.name = "kekdsfgfgdfgdfghfhtyurcvbcbbcvbcvbcvhjhjhjhjhjhjhjhjhjhjk";
    item1.userIds = {3,2,1};
    item1.lastMessage = "netghghghghghghghghghghghghghghgh";
    item1.time = "23:44";
    for(int i = 0 ; i < 30; ++i){
        item1.time = QString::number(i);     
        groupModel->addItem(item1);
    }

    chatModel = new ChatModel();
    ui->chatList->setModel(chatModel);
    ui->chatList->setItemDelegate(new ChatDelegate);
    //ui->chatList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->chatList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connect(ui->menuButton,&CustomButton::clicked,menuWidget,&MenuWidget::show);
    connect(ui->menuButton,&CustomButton::clicked,this,&MainWidget::menuClicked);
    connect(ui->sendButton,&CustomButton::clicked,this,&MainWidget::sendMessageFromInput);

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
    message.text = ui->messageInput->text().toStdString();
    qDebug() << QString::fromStdString(message.text);
    message.name = "kostya";
    message.timesend  = 0;
    chatModel->createMessage(message);
    ui->messageInput->clear();
    emit ui->chatList->doItemsLayout();
}
