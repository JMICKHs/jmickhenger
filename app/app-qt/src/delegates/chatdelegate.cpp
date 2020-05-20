#include "chatdelegate.h"
#include "app-qt/src/custommbutton/custombutton.h"
#include <QApplication>
#include <QMouseEvent>
#include <QFontMetrics>
#include <QDebug>

ChatDelegate::ChatDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{
    avatar = new QPixmap("/home/kostikan/jmickhenger/app/img/standartAvatar.jpg");
    check = new QPixmap("/home/kostikan/jmickhenger/app/img/check.png");
    uncheck = new QPixmap("/home/kostikan/jmickhenger/app/img/unchecked.png");
}

QSize ChatDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Msg item = index.model()->data(index).value<Msg>();
    QRect MessageRect = option.rect;
    MessageRect.setY(MessageRect.y() + 15);
    MessageRect.setX(45);
    MessageRect.setWidth(option.widget->width() - 80);
    QFontMetrics fMetrics(option.font);
    int height = fMetrics.boundingRect(QRect(0,0,option.widget->width() - 240,0),Qt::TextWordWrap,QString::fromStdString(item.text)).height();
    if(height <= 45)
        return QSize(option.widget->width(),baseItemHeight);
    else {
         return QSize(option.widget->width(),height + 15);
    }
}

bool ChatDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    QRect ButtonRect = option.rect;
    ButtonRect.setWidth(45);
    if (mouse_event->button() == Qt::LeftButton)
    {
         if(ButtonRect.contains(mouse_event->pos())) {
             qDebug() << "kek";
         }
    }
}

void ChatDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Msg item = index.model()->data(index).value<Msg>();
    QStyleOptionViewItem myOpt = option;
    myOpt.displayAlignment = Qt::AlignLeft;
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
        painter->restore();
    }


    painter->save();
    QRect NameRect = myOpt.rect;
    NameRect.setHeight(baseTextHeight);
    NameRect.setX(avatarSize.width() + textOffset);
    NameRect.setWidth(width - rightMessageOffset);

    painter->setFont(f);
    painter->setPen(QColor(76,148,224));
    painter->drawText(NameRect, Qt::TextSingleLine,
                   item.nickname);

//    QRect TimeRect = myOpt.rect;
//    TimeRect.setHeight(baseTextHeight);
//    TimeRect.setX(45);
//    TimeRect.setWidth(width - 45);

    QRect MessageRect = myOpt.rect;
    MessageRect.setY(MessageRect.y() + mainMessageTopOffset);
    MessageRect.setX(avatarSize.width() + textOffset);
    MessageRect.setWidth(width - rightMessageOffset);

    painter->setFont(f);
    painter->setPen(palette.text().color());
    painter->drawText(MessageRect, Qt::TextWrapAnywhere,
                   QString::fromStdString(item.text));

    painter->restore();
    painter->save();

//    QPen pen;
//    painter->setRenderHint(QPainter::Antialiasing);
//    pen.setWidth(1);
//    pen.setColor(Qt::white);
//    painter->setPen(pen);
//    painter->translate(QPointF(myOpt.widget->width() - 54,myOpt.widget->height() - 54));
//    painter->drawRoundedRect(5, 5, 40, 40, 100, 100);
//    pen.setColor(Qt::blue);
//    painter->setPen(pen);
//    painter->drawRoundedRect(5, 5, 40, 40, 100, 100);
//    painter->translate(QPointF(0,6));
//    painter->drawLine(16,13,25,25);
//    painter->translate(QPointF(25,25));
//    painter->drawLine(0,0, 10,-13);
//    painter->restore();

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
         else{
              QPixmap checkScaled = check->scaled(20, 20, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
              QBrush check(checkScaled);
              painter->setRenderHint(QPainter::Antialiasing);
              painter->setBrush(check);
              painter->translate(QPointF(rect.width()-30,rect.y() + 10));
              painter->fillRect(checkScaled.rect(),Qt::transparent);
              painter->drawPixmap(checkScaled.rect(),checkScaled);
         }
    }
     painter->restore();
}


