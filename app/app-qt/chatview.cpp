#include "chatview.h"
#include <QResizeEvent>
#include <QDebug>
#include <QPalette>

ChatView::ChatView(QWidget *parent)
    :QListView(parent)
{
    this->setStyleSheet(                   
                        "QListWidget{ outline: 0;}"
                        "QListWidget::item:hover{   background-color:  rgb(240, 240, 243);selection-color: transperent;}"
                        "QListWidget::item:selected{ background-color:  rgb(235, 235, 248);selection-color: transperent;}"
                       );

//    background = new QImage("G://download//priroda-more-okean-voda-volny.jpg");
//    QPalette palette = this->palette();
//    palette.setBrush(this->backgroundRole(), QBrush(*background));
    //    this->setPalette(palette);
     this->setAutoFillBackground(true);
}

void ChatView::resizeEvent(QResizeEvent *event)
{
   emit this->doItemsLayout();
}
