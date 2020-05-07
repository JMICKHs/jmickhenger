#include "chatview.h"
#include <QResizeEvent>
#include <QDebug>
#include <QPalette>

ChatView::ChatView(QWidget *parent)
    :QListView(parent)
{
     this->setFocusPolicy(Qt::StrongFocus);
    this->setStyleSheet(                   
                        "QListWidget{ outline: 0;}"
                        "QListWidget::item:hover{   background-color:  rgb(240, 240, 243);selection-color: transperent;}"
                        "QListWidget::item:selected{ background-color:  rgb(235, 235, 248);selection-color: transperent;}"
                       );

     this->setAutoFillBackground(true);
}

void ChatView::resizeEvent(QResizeEvent *event)
{
    emit this->doItemsLayout();
}

void ChatView::rowsInserted(const QModelIndex &parent, int start, int end)
{
    this->scrollToBottom();
}

void ChatView::mousePressEvent(QMouseEvent *event)
{
    QRegion scrollDownReg(this->size().width() - 50,this->size().height() - 50,40,40,QRegion::Ellipse);
    qDebug() <<scrollDownReg.boundingRect().x()<< " " <<scrollDownReg.boundingRect().y();
    if (event->button() == Qt::LeftButton)
    {
         if( scrollDownReg.contains(event->pos())) {
             this->scrollToBottom();
         }
    }
}

void ChatView::wheelEvent(QWheelEvent *e)
{
    emit this->repaint();
}

void ChatView::scrollWhileDataChandeg(){
    this->scrollToBottom();
}
