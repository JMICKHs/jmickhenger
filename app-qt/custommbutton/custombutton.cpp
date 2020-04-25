#include "custombutton.h"
#include <QPainter>

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
//    QIcon *icon = new QIcon("G:/download/71acb914d3d6f1239cbd1863b90c2df2.jpg");
//    this->setButtonIcon(*icon);
    this->setStyleSheet("QPushButton{ border: 0px solid ;background-image: url(G:/download/71acb914d3d6f1239cbd1863b90c2df2.jpg); border-radius: 14px; background: rgb(227, 227, 0);}");


    this->setMaximumSize(35,35);
    this->setMinimumSize(25,25);
    QSize size{35,35};
    this->setIconSize(size);
  //  this->setWindowFlag(Qt::FramelessWindowHint);
    this->setCursor(Qt::PointingHandCursor);

//    QImage image{"G:/download/71acb914d3d6f1239cbd1863b90c2df2.jpg"};
//    image.convertToFormat(QImage::Format_ARGB32);


//    int imgsize = std::min(image.width(), image.height());
//    QRect rect = QRect(
//        (image.width() - imgsize) / 2,
//        (image.height() - imgsize) / 2,
//        imgsize,
//        imgsize
//    );
//    image = image.copy(rect);


//    QImage out_img = QImage(imgsize, imgsize, QImage::Format_ARGB32);
//    out_img.fill(Qt::transparent);

//    QBrush brush = QBrush(image) ;
//    QPainter painter;
//      painter.drawImage(rect,image,QRect(40,40,40,40));
//    painter.setBrush(brush);
//    painter.setPen(Qt::NoPen);
//    painter.setRenderHint(QPainter::Antialiasing, true) ;
//    painter.drawEllipse(0, 0, imgsize, imgsize);
//    painter.drawImage(rect,image,QRect(40,40,40,40));
//    painter.end();


//    QPixmap pm = QPixmap::fromImage(out_img);
//    this->setButtonIcon(QIcon(pm));

}

void CustomButton::setButtonIcon(const QIcon &icon)
{
    this->setIcon(icon);
}

void CustomButton::setButtonRect(const QRect &rect)
{
    this->setGeometry(rect);
}

void CustomButton::clickedById()
{
    emit sendId(id);
}

