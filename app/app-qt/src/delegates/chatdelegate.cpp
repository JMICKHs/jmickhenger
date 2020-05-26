#include "chatdelegate.h"
#include "app-qt/src/custommbutton/custombutton.h"
#include <QApplication>
#include <QMouseEvent>
#include <QFontMetrics>
#include <QDebug>
#include <QTextLine>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>

ChatDelegate::ChatDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{
    avatar = new QPixmap(":/imges/standartAvatar.jpg");
    check = new QPixmap(":/imges/check.png");
    uncheck = new QPixmap(":/imges/unchecked.png");
    showPicture.move(parent->pos().x() + parent->size().width()/(4),
                     parent->pos().y() + parent->size().height()/(4));
    showPicture.setWindowFlag(Qt::Popup);
    showPicture.resize(900,600);

}

QSize ChatDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Msg item = index.model()->data(index).value<Msg>();
    QRect MessageRect = option.rect;
    MessageRect.setY( mainMessageTopOffset + option.rect.y());
    MessageRect.setX(avatarSize.width() + textOffset);
    MessageRect.setWidth(option.widget->width() - 80);
    QFontMetrics fMetrics(option.font);
    int height = fMetrics.boundingRect(QRect(0,0,option.widget->width() - MessageRect.x() - 35,0),Qt::TextWordWrap,QString::fromStdString(item.text)).height();
    if(item.img != nullptr){
        height += 200;
    }
    if(height <= 45)
        return QSize(option.widget->width(),baseItemHeight);
    else {
         return QSize(option.widget->width(),height + 15);
    }
}

bool ChatDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Msg item = index.model()->data(index).value<Msg>();
    QRect NameRect = option.rect;
    NameRect.setHeight(baseTextHeight);
    NameRect.setX(avatarSize.width() + textOffset);
    NameRect.setWidth(option.widget->width() - rightMessageOffset);

    QRect MessageRect =option.rect;
    MessageRect.setY(MessageRect.y() + mainMessageTopOffset);
    MessageRect.setX(avatarSize.width() + textOffset);
    MessageRect.setWidth(option.widget->width() - rightMessageOffset);
    QFontMetrics fMetrics(option.font);
    int height = fMetrics.boundingRect(QRect(0,0,option.widget->width() - 240,0),Qt::TextWordWrap,QString::fromStdString(item.text)).height();
   // QPixmap map = item.image->scaled(200,200,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QRect pictureRect = QRect(QPoint(avatarSize.width() + textOffset,MessageRect.y()+height),QSize(200,200));

    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    QRect ButtonRect = option.rect;
    ButtonRect.setWidth(45);
    if (option.rect.contains(mouse_event->pos()))
    {
         if(ButtonRect.contains(mouse_event->pos())) {
             qDebug() << "ButtonRect";
         }
         if(NameRect.contains(mouse_event->pos())){
             qDebug() <<" Namerect";

             //QLabel* editor = qobject_cast<QLabel*>(this->createEditor(nullptr,option,index));
             //editor->setTextInteractionFlags(Qt::TextSelectableByMouse);
             //editor->setCursor(Qt::IBeamCursor);
             //editor->setText(item.nickname);
             //editor->repaint(NameRect);
        }
         if(pictureRect.contains(mouse_event->pos()) && item.img != nullptr){
            qDebug() <<"PictureRect";
            QPixmap pix1 = item.img->scaled(600,600,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            showPicture.resize(pix1.size());
            QPalette palette;
            palette.setBrush(showPicture.backgroundRole(), QBrush(pix1));
            showPicture.setPalette(palette);
            showPicture.setAutoFillBackground(true);
            showPicture.show();
        }
    }
    return  QAbstractItemDelegate::editorEvent(event,model,option,index);
}

void ChatDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Msg item = index.model()->data(index).value<Msg>();
    QStyleOptionViewItem myOpt = option;
    myOpt.displayAlignment =  Qt::AlignVCenter;
    painter->save();
    painter->setClipping(true);

    QRect rect(myOpt.rect);
    rect.setWidth(option.widget->width());
    rect.setHeight(sizeHint(option,index).height());

    const QPalette &palette(myOpt.palette);
    QFont f(myOpt.font);
    painter->fillRect(rect, myOpt.state & QStyle::State_Selected ?
                             palette.highlight().color() :
                             palette.light().color());
    painter->setFont(myOpt.font);

    int width = sizeHint(option,index).width();
    QFontMetrics font(f);

    if(item.avatar != ""){

        QString path = ":/imges/" + item.avatar;
        QPixmap pix(path);
        QPixmap pix1 = pix.scaled(avatarScale, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

        QBrush brush(pix1);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(brush);
        painter->translate(QPointF(0,myOpt.rect.y()));
        painter->drawRoundedRect(QRect(QPoint(offset),avatarSize), avatarRadius, avatarRadius);
    }
    painter->restore();

    painter->save();
    QRect NameRect = myOpt.rect;
    NameRect.setHeight(baseTextHeight);
    NameRect.setX(avatarSize.width() + textOffset);
    NameRect.setWidth(width - rightMessageOffset);

    painter->setFont(f);
    painter->setPen(QColor(76,148,224));
    painter->drawText(NameRect, Qt::TextSingleLine,
                   item.nickname);

    QRect TimeRect = myOpt.rect;
    TimeRect.setHeight(baseTextHeight);
    TimeRect.setX(myOpt.widget->width() - 80);
    TimeRect.setWidth(width - rightMessageOffset);
    painter->drawText(TimeRect, Qt::TextSingleLine,
                   item.time);

    QRect MessageRect = myOpt.rect;
    MessageRect.setY(MessageRect.y() + mainMessageTopOffset);
    MessageRect.setX(avatarSize.width() + textOffset);
    MessageRect.setWidth(width - rightMessageOffset - 5);

    painter->setFont(f);
    painter->setPen(palette.text().color());
    painter->drawText(MessageRect, Qt::AlignVCenter | Qt::AlignLeft | Qt::TextWordWrap,
                   QString::fromStdString(item.text));

    painter->restore();
    painter->save();
    if(item.img != nullptr){

        QFontMetrics fMetrics(option.font);
        int height = fMetrics.boundingRect(QRect(0,0,option.widget->width() - 240,0),Qt::TextWordWrap,QString::fromStdString(item.text)).height();

        QPixmap map = item.img->scaled(200,200,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        QBrush brush(map);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(brush);
        painter->translate(QPoint(avatarSize.width() + textOffset,MessageRect.y()+height));
        painter->drawRect(QRect(QPoint(0,0),map.size()));
    }
    painter->restore();
    painter->save();

     if(item.type != MessageType::OTHER_MESSAGE){
         if(item.type == MessageType::SELF_MESSAGE_IN_PROGRESS){
              QPixmap checkScaled = uncheck->scaled(15, 15, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
              QBrush check(checkScaled);
              painter->setRenderHint(QPainter::Antialiasing);
              painter->setBrush(check);
              painter->translate(QPointF(rect.width()-30,rect.y() + 10));
              painter->fillRect(checkScaled.rect(),Qt::transparent);
              painter->drawPixmap(checkScaled.rect(),checkScaled);
         }
         if(item.type == MessageType::SELF_MESSAGE_DONE){
              QPixmap checkScaled = check->scaled(20, 20, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
              QBrush check(checkScaled);
              painter->setRenderHint(QPainter::Antialiasing);
              painter->setBrush(check);
              painter->translate(QPointF(rect.width()-30,rect.y() + 10));
              painter->fillRect(checkScaled.rect(),Qt::transparent);
              painter->drawPixmap(checkScaled.rect(),checkScaled);
         }
         if(item.type == MessageType::READ_MESSAGE){

             QPixmap checkScaled = check->scaled(20, 20, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
             QBrush check(checkScaled);
             painter->setRenderHint(QPainter::Antialiasing);
             painter->setBrush(check);
             painter->translate(QPointF(rect.width()-30,rect.y() + 10));
             painter->fillRect(checkScaled.rect(),Qt::transparent);
             painter->drawPixmap(checkScaled.rect(),checkScaled);

             painter->translate(QPointF(-10,0));
             painter->drawPixmap(checkScaled.rect(),checkScaled);
         }
    }
     painter->restore();
}


void ChatDelegate::setEditorData(QWidget* editor, const QModelIndex &index) const{
    qDebug() <<"setData";
    QStyledItemDelegate::setEditorData(editor,index);
     QLabel* le= qobject_cast<QLabel*>(editor);
    if(le){
         QString text = index.model()->data(index).value<Msg>().nickname;
                le->setText(text);
        }

}

QWidget *ChatDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() <<"createEDitor";
    QStyledItemDelegate::createEditor(parent,option,index);
    QString text = QString::fromStdString(index.model()->data(index).value<Msg>().text);
    QLabel* editor = new QLabel(text,parent);
    return editor;
}

void ChatDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() <<"updateGeometry";
    QStyledItemDelegate::updateEditorGeometry(editor,option,index);
    editor->setGeometry(option.rect);
}
