#include "menuwidget.h"
#include "ui_menuwidget.h"
#include "netlib/AppNetwork.h"
#include <QDebug>

MenuWidget::MenuWidget(QWidget *parent)
    :QFrame(parent),
    ui(new Ui::MenuWidget)
{
    ui->setupUi(this);
    this->setLayout(ui->mainLayout);
    this->setFrameShadow(QFrame::Raised);
    this->setMinimumWidth(260);
    this->setWindowFlags(Qt::Popup);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    ui->pushButton->setFixedSize(70,70);
    ui->pushButton->setFlat(true);

    QPixmap pix1(":/imges/standartAvatar.jpg");
    QPixmap pix(pix1.scaled(55,55, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    QPalette palette;
    palette.setBrush(ui->pushButton->backgroundRole(), QBrush(pix));
    ui->pushButton->setAutoFillBackground(true);
    ui->pushButton->setPalette(palette);
    QRect rect(0,0,55,55);
    QRegion region(rect, QRegion::Ellipse);
    ui->pushButton->setMask(region);

    avatWidget = new SetAvatarWidget(parent);
    setting = new SettingWidget(parent);
    friendsWidget = std::shared_ptr<CreateGroupWidget>(new CreateGroupWidget(parent));
    connect(friendsWidget.get(),&CreateGroupWidget::closeMenu,this,&MenuWidget::close);
    connect(avatWidget,&SetAvatarWidget::avatarChangeSignal,this,&MenuWidget::on_image_change);
    connect(this,&MenuWidget::getListFriendSignal,friendsWidget.get(),&CreateGroupWidget::getListFriend);
}

MenuWidget::~MenuWidget()
{
    delete ui;
}

CreateGroupWidget *MenuWidget::getCreateWidget()
{
    return friendsWidget.get();
}

void MenuWidget::setPosition()
{
    this->setFocus();
    this->raise();
}

void MenuWidget::setName(const QString &name)
{
    ui->nickName->setText(name);
}

void MenuWidget::on_nickname_rename(const QString &nick)
{
    ui->nickName->setText(nick);
}

void MenuWidget::on_createGroupButton_clicked()
{
    friendsWidget->setWidget(WidgetType::CREATE_GROUP);
    friendsWidget->show();
    friendsWidget->getFriendsModel()->Clear();
    emit getListFriendSignal();
}

void MenuWidget::on_contactsButton_clicked()
{
    friendsWidget->setWidget(WidgetType::CONTACTS);
    friendsWidget->show();
    friendsWidget->getFriendsModel()->Clear();
    emit getListFriendSignal();
}

void MenuWidget::on_image_change(const QString &str)
{
    QString path = ":/imges/" + str;
    QPixmap pix1(path);
    QPixmap pix(pix1.scaled(55,55, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    QPalette palette;
    palette.setBrush(ui->pushButton->backgroundRole(), QBrush(pix));
    ui->pushButton->setAutoFillBackground(true);
    ui->pushButton->setPalette(palette);
    QRect rect(0,0,55,55);
    QRegion region(rect, QRegion::Ellipse);
    ui->pushButton->setMask(region);

}

void MenuWidget::on_pushButton_clicked()
{
    avatWidget->show();
    avatWidget->move(parentWidget()->pos().x() + parentWidget()->size().width()/(4),
               parentWidget()->pos().y() + parentWidget()->size().height()/(4));
}



void MenuWidget::on_exitButton_clicked()
{
    emit closeAndExit();
}

void MenuWidget::on_settingsButton_clicked()
{
    setting->show();
    setting->move(parentWidget()->pos().x() + parentWidget()->size().width()/(4),
               parentWidget()->pos().y() + parentWidget()->size().height()/(4));
}
