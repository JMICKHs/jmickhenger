#include "custombutton.h"

CustomButton::CustomButton(QWidget *parent)
    :QPushButton(parent)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setCursor(Qt::PointingHandCursor);
    this->setStyleSheet("QPushButton{background:transparent; border:none}"

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
    this->setStyleSheet("QPushButton{ border: 0px solid ;background-image: url(G:/download/71acb914d3d6f1239cbd1863b90c2df2.jpg); border-radius: 14px; background: rgb(227, 227, 0);}");


    this->setMaximumSize(35,35);
    this->setMinimumSize(25,25);
    QSize size{35,35};
    this->setIconSize(size);
    this->setCursor(Qt::PointingHandCursor);
}

void CustomButton::setButtonIcon(const QIcon &icon)
{
    this->setIcon(icon);
}

void CustomButton::setButtonRect(const QRect &rect)
{
    this->setGeometry(rect);
}


