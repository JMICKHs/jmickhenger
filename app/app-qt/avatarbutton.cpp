#include "avatarbutton.h"

AvatarButton::AvatarButton(QWidget *parent)
    :QPushButton(parent)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setCursor(Qt::PointingHandCursor);
    QIcon icon("G://download//unnamed.jpg");
    this->setIcon(icon);
}
