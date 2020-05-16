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
    friendModel = std::make_shared<FriendsModel>();
    friendModel->addCallbacks();

    this->setWindowFlags(Qt::Popup);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    proxy = new FriendModelProxy();
    proxy->setSourceModel(friendModel.get());
    UserInf inf;
    inf.id = 3;
    inf.login = "str";
    UserInf inf1;
    inf1.id = 4;
    inf1.login = "kek";
    friendModel->addFriend(inf);
    friendModel->addFriend(inf1);
    connect(this,&CreateGroupWidget::text_changed,proxy,&FriendModelProxy::search_String_Changed);
    connect(this,&CreateGroupWidget::text_changed,proxy,&FriendModelProxy::search_String_Changed);

    ui->createGroupView->setModel(proxy);
    ui->friendsView->setModel(proxy);
    ui->createGroupView->setItemDelegate(new friendsDelegate);
    ui->friendsView->setItemDelegate(new friendsDelegate);
    ui->createGroupView->setSelectionMode(QAbstractItemView::MultiSelection);
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

void CreateGroupWidget::on_pushButton_clicked()
{
    this->close();
}

void CreateGroupWidget::on_closeContactsButton_clicked()
{
    this->close();
}

void CreateGroupWidget::on_SearchEditToCreateGroup_textChanged(const QString &arg1)
{
    emit text_changed(arg1);
}

void CreateGroupWidget::on_SearchLineEditFriends_textChanged(const QString &arg1)
{
    emit text_changed(arg1);
}

void CreateGroupWidget::on_pushButton_2_clicked()
{
    if(!ui->createGroupView->selectionModel()->hasSelection())
        return;
    else
    {
        QModelIndexList indexList = ui->createGroupView->selectionModel()->selectedRows();
        inf::ChatRoom item;
        std::vector<int> usrIds;
        for(auto& indexData : indexList){
            usrIds.push_back(indexData.data().value<UserInf>().id);
            qDebug() << indexData.data().value<UserInf>().id;
        }
        item.idUsers = std::move(usrIds);
        item.name = ui->lineEdit->text().toStdString();
        emit groupCreated(item);
        close();
    }
}
