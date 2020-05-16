#include "setavatarwidget.h"
#include "ui_setavatarwidget.h"
#include <vector>

SetAvatarWidget::SetAvatarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetAvatarWidget)
{
    ui->setupUi(this);
    this->resize(500,300);
    this->setWindowFlags(Qt::Popup);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->setLayout(ui->horizontalLayout);
    avatars.emplace_back(baseAvatars::AVATAR1,"/home/kostikan/jmickhenger/app/img/standartAvatar.jpg");
    avatars.emplace_back(baseAvatars::AVATAR2,"/home/kostikan/jmickhenger/app/img/img518924.png");
    ui->comboForAvatars->addItem("avatar1");
    ui->comboForAvatars->addItem("avatar2");
    ui->avatar->setFixedSize(300,300);
    QPixmap pix1(avatars[0].second);
    QPixmap pix(pix1.scaled(ui->avatar->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    QPalette palette;
    palette.setBrush(ui->avatar->backgroundRole(), QBrush(pix));
    ui->avatar->setAutoFillBackground(true);
    ui->avatar->setPalette(palette);
}

SetAvatarWidget::~SetAvatarWidget()
{
    delete ui;
}

void SetAvatarWidget::on_acceptButton_clicked()
{
   emit avatarChangeSignal(avatars[ui->comboForAvatars->currentIndex()].second);
   this->close();
}


void SetAvatarWidget::on_comboForAvatars_currentIndexChanged(int index)
{
    QPixmap pix1(avatars[index].second);
    QPixmap pix(pix1.scaled(ui->avatar->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    QPalette palette;
    palette.setBrush(ui->avatar->backgroundRole(), QBrush(pix));
    ui->avatar->setAutoFillBackground(true);
    ui->avatar->setPalette(palette);

}
