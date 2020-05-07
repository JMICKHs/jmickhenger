#include "chatinput.h"
#include <QKeyEvent>

ChatInput::ChatInput(QWidget *parent)
    :QPlainTextEdit(parent)
{
}

void ChatInput::keyPressEvent(QKeyEvent *e)
{
    QPlainTextEdit::keyPressEvent(e);
    if(e->key() == Qt::Key_Enter && e->key() != Qt::Key_Shift){
        emit sendMessageOnEnter();

    }

}
