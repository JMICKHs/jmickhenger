#include "chatinput.h"
#import <QKeyEvent>
#import <QMimeData>
#import <QDebug>
#import <QImage>

ChatInput::ChatInput(QWidget *parent)
    :QPlainTextEdit(parent)
{
    this->setAcceptDrops(true);
}

void ChatInput::keyPressEvent(QKeyEvent *e)
{
    QPlainTextEdit::keyPressEvent(e);
    if(e->key() == Qt::Key_Return && !(e->modifiers() & Qt::ShiftModifier)){
        if(changeMsg == false){
            emit sendMessageOnEnter();
        }
        else
        {
            emit sendMessageForChange();
            changeMsg = false;
        }
        this->setMaximumHeight(this->minimumSize().height());
        this->clear();
    }
    if(e->key() == Qt::Key_Return && (e->modifiers() & Qt::ShiftModifier)){
       this->setMaximumHeight(this->size().height() + this->fontMetrics().height());
        baseHeight = this->fontMetrics().height();
      // emit changeSpacer(this->fontMetrics().height());
    }
}

void ChatInput::dragEnterEvent(QDragEnterEvent *e)
{
    e->accept();
    qDebug() << "here";
    if (e->proposedAction() == Qt::MoveAction) {
           e->acceptProposedAction();
    }
    QString filePath = e->mimeData()->urls()[0].toLocalFile();
    image = QPixmap(filePath);
    created = true;
}

void ChatInput::dropEvent(QDropEvent *e)
{

}

void ChatInput::textForChange(const QString &str)
{
    changeMsg = true;
    this->setPlainText(str);
}
