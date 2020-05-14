#include "creategroupwidget.h"
#include "ui_creategroupwidget.h"
#include <app-qt/src/delegates/friendsdelegate.h>
#include <QDebug>

CreateGroupWidget::CreateGroupWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::CreateGroupWidget)
{
    ui->setupUi(this);
    createWidget = new QWidget(this);
    this->resize(400,400);
    createWidget->setMaximumSize(400,400);
    contactsWidget = new QWidget(this);
    contactsWidget->setMaximumSize(400,400);
    this->addWidget(createWidget);
    createWidget->setLayout(ui->CreateGroupLayout);
    this->addWidget(contactsWidget);
    contactsWidget->setLayout(ui->ContactsLayout);
    friendModel = make_shared<FriendsModel>();
    friendModel->addCallbacks();


    this->setWindowFlags(Qt::Popup);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    UserInf inf;
    inf.id = 3;
    inf.login = "str";
    UserInf inf1;
    inf1.id = 4;
    inf1.login = "kek";
    friendModel->addFriend(inf);
    friendModel->addFriend(inf1);

    ui->listView->setModel(friendModel.get());
    ui->listView_2->setModel(friendModel.get());

    ui->listView->setItemDelegate(new friendsDelegate);
    ui->listView_2->setItemDelegate(new friendsDelegate);

}

CreateGroupWidget::~CreateGroupWidget()
{
    delete ui;
}

void CreateGroupWidget::setWidget(WidgetType type)
{
     this->move(parentWidget()->pos().x() + parentWidget()->size().width()/(4),
                parentWidget()->pos().y() + parentWidget()->size().height()/(4));
    if(type == WidgetType::CONTACTS)
        setCurrentWidget(contactsWidget);
    else
        setCurrentWidget(createWidget);
}
