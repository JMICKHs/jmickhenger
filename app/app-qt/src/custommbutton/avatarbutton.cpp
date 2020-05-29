#include "avatarbutton.h"

AvatarButton::AvatarButton(QWidget *parent) : QPushButton(parent)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setCursor(Qt::PointingHandCursor);
}

void AvatarButton::paintEvent(QPaintEvent *event)
{

}
