#include "setavatarwidget.h"
#include "ui_setavatarwidget.h"
#include <vector>

SetAvatarWidget::SetAvatarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetAvatarWidget)
{
    ui->setupUi(this);
    this->resize(500,300);
    this->setFocus(Qt::PopupFocusReason);
    this->setWindowFlags(Qt::ToolTip);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->setLayout(ui->horizontalLayout);
    avatars.emplace_back(baseAvatars::AVATAR1,"standartAvatar.jpg");
    avatars.emplace_back(baseAvatars::AVATAR2,"avatar2.jpg");
    avatars.emplace_back(baseAvatars::AVATAR3,"avatar3.jpg");
    avatars.emplace_back(baseAvatars::AVATAR4,"avatar4.jpg");
    avatars.emplace_back(baseAvatars::AVATAR5,"avatar5.jpg");
    avatars.emplace_back(baseAvatars::AVATAR6,"avatar6.jpg");
    ui->comboForAvatars->addItem("avatar1");
    ui->comboForAvatars->addItem("avatar2");
    ui->comboForAvatars->addItem("avatar3");
    ui->comboForAvatars->addItem("avatar4");
    ui->comboForAvatars->addItem("avatar5");
    ui->comboForAvatars->addItem("avatar6");
    ui->avatar->setFixedSize(300,300);
    QString path = ":/imges/" + avatars[0].second;
    QPixmap pix1(path);
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
    QString path = ":/imges/" + avatars[index].second;
    QPixmap pix1(path);
    QPixmap pix(pix1.scaled(ui->avatar->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    QPalette palette;
    palette.setBrush(ui->avatar->backgroundRole(), QBrush(pix));
    ui->avatar->setAutoFillBackground(true);
    ui->avatar->setPalette(palette);

}
