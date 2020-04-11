#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

}

MainWindow::~MainWindow()
{

}

void MainWindow::linkObjects()
{
    mainHLayout = new QHBoxLayout;
    mainHLayout->setContentsMargins(0,0,0,0);
    mainHLayout->setMargin(0);

    searchHLayout = new QHBoxLayout;
    topHLayout    = new QHBoxLayout;
    bottomHLayout = new QHBoxLayout;

    searchHLayout->addWidget(menu);
    searchHLayout->addWidget(search);
    searchHLayout->setMargin(5);
    searchHLayout->setSpacing(4);

    firstVLayout = new QVBoxLayout;
    firstVLayout->setMargin(0);
    firstVLayout->setSpacing(0);

    firstVLayout->addLayout(searchHLayout);
    firstVLayout->addWidget(listObject);

    topHLayout = new QHBoxLayout;
    topHLayout->addWidget(groupName);
    topHLayout->addWidget(groupSearch);
    topHLayout->addWidget(groupActions);
    topHLayout->setMargin(5);
    topHLayout->setSpacing(2);

    bottomHLayout  = new QHBoxLayout;
    bottomHLayout->addWidget(inputFiles);
    bottomHLayout->addWidget(textMessage);
    bottomHLayout->addWidget(send);
    bottomHLayout->setMargin(5);
    bottomHLayout->setSpacing(2);

    secondVLayout = new QVBoxLayout;
    secondVLayout->setMargin(0);
    secondVLayout->setSpacing(0);
    secondVLayout->addLayout(topHLayout);
    secondVLayout->addWidget(chatList);
    secondVLayout->addLayout(bottomHLayout);

    leftSide->setLayout(firstVLayout);
    rightSide->setLayout(secondVLayout);
    splitter->addWidget(leftSide);
    splitter->addWidget(rightSide);
    splitter->setCollapsible(0,0);
    splitter->setCollapsible(1,0);

    mainHLayout->addWidget(splitter);
    mainHLayout->setSpacing(0);
    this->setLayout(mainHLayout);
    connect(menu,SIGNAL(clicked()),menuWidget,SLOT(show()));
    connect(menu,SIGNAL(clicked()),this,SLOT(menuClicked()));
    connect(send,SIGNAL(clicked()),this,SLOT(messageButtonClicked()));
    connect(this,SIGNAL(sendMessage(const Message&)),chatList,SLOT(newMessage(const Message&)));
}

void MainWindow::createObjects()
{
    splitter = new QSplitter(Qt::Horizontal);
    splitter->setSizes(QList<int>() << 100 << 100);
    splitter->setHandleWidth(0);
    listObject = new GroupListObject(this);
    chatList = new ChatList();

    search = new QLineEdit(this);
    search->setMinimumHeight(30);
    QIcon icon;
    icon.addFile("G://download//iconfinder_menu-alt_134216.png");
    menu = new CustomButton(this);
    menu->setButtonIcon(icon);

    leftSide = new QWidget(this);
    leftSide->setMinimumHeight(200);
    rightSide = new QWidget(this);
    rightSide->setMinimumHeight(300);

    groupName = new QLabel("GROUP NAME");
    groupName->setMinimumHeight(30);
    groupSearch = new CustomButton(this);

    groupActions = new CustomButton(this);

    inputFiles = new CustomButton(this);
    send = new CustomButton(this);
    textMessage = new QLineEdit(this);
    textMessage->setMinimumHeight(30);

    this->resize(800,600);
    menuWidget = new MenuWidget(nullptr,this->size());
    linkObjects();
    this->show();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    leftSide->setMinimumWidth( event->size().width()/3.0);
    rightSide->setMinimumWidth( event->size().width()/2.1);
    menuWidget->resize(0,event->size().height());
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    menuWidget->move(event->pos());
}

ChatList &MainWindow::getChatList()
{
    return *chatList;
}

void MainWindow::menuClicked(){
    menuWidget->move(QPoint(geometry().x(),geometry().y()));
    emit menuWidget->setPosition();
}

void MainWindow::messageButtonClicked()
{
    Message message;
    message.text = textMessage->text();
    emit sendMessage(message);
}

