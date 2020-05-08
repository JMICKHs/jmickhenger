#include "chatinput.h"
#include <QKeyEvent>

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
