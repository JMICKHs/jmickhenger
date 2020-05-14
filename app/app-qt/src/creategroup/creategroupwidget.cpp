#include "creategroupwidget.h"
#include "ui_creategroupwidget.h"

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
}

CreateGroupWidget::~CreateGroupWidget()
{
    delete ui;
}

void CreateGroupWidget::setWidget(WidgetType type)
{
    if(type == WidgetType::CONTACTS)
        setCurrentWidget(contactsWidget);
    else
        setCurrentWidget(createWidget);
}
