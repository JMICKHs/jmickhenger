#include "chatinput.h"
#include <QKeyEvent>
#include <QMimeData>
#include <QDebug>
#include <QImage>

ChatInput::ChatInput(QWidget *parent)
    :QPlainTextEdit(parent)
{

}

void ChatInput::keyPressEvent(QKeyEvent *e)
{
    QPlainTextEdit::keyPressEvent(e);
    if(e->key() == Qt::Key_Return && !(e->modifiers() & Qt::ShiftModifier)){
        emit sendMessageOnEnter();
        this->setMaximumHeight(this->minimumSize().height());
    }
    if(e->key() == Qt::Key_Return && e->modifiers() & Qt::ShiftModifier){
       this->setMaximumHeight(this->size().height() + this->fontMetrics().height());
    }
}

void ChatInput::dragEnterEvent(QDragEnterEvent *e)
{
    qDebug() << "here";
    QString filePath = e->mimeData()->urls()[0].toLocalFile();
    image = QPixmap(filePath);
    created = true;

}
