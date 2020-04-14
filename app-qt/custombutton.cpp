#include "custombutton.h"

CustomButton::CustomButton(QWidget *parent)
    :QPushButton(parent)
{
    this->setMaximumSize(30,30);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setCursor(Qt::PointingHandCursor);
    this->setStyleSheet("QPushButton{background: transparent;}"
                        "QPushButton:hover{ background: rgb(227, 227, 229); border:none;}"
                        "QPushButton:pressed{  background-color: rgb(218, 218, 220); background-position: bottom center;  background-repeat: repeat-xy;  widget-animation-duration: 100;}");


}

CustomButton::CustomButton(const char *name, QSize size, QWidget *parent)
    :QPushButton(parent)
{
    this->setStyleSheet("QPushButton{background: transparent;}"
                        "QPushButton:hover{ background: rgb(227, 227, 229); border:none;}"
                        "QPushButton:pressed{ background-color: rgb(218, 218, 220);  background-position: bottom center; background-repeat: repeat-xy; widget-animation-duration: 100;}");

    this->setMinimumHeight(size.height());
    this->setText(QString(name));
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setCursor(Qt::PointingHandCursor);
}

CustomButton::CustomButton(int id, QWidget *parent)
  :QPushButton(parent)
{
    this->id = id;
    this->setMaximumSize(30,30);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setCursor(Qt::PointingHandCursor);
    this->setStyleSheet("QPushButton{background: transparent;}"
                        "QPushButton:hover{ background: rgb(227, 227, 229); border:none;}"
                        "QPushButton:pressed{  background-color: rgb(218, 218, 220); background-position: bottom center;  background-repeat: repeat-xy;  widget-animation-duration: 100;}");

}

void CustomButton::setButtonIcon(const QIcon icon)
{
    this->setIcon(icon);
}

void CustomButton::setButtonRect(const QRect rect)
{
    this->setGeometry(rect);
}

void CustomButton::clickedById()
{
    emit sendId(id);
}

