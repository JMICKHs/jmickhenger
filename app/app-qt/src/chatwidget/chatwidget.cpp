#include "chatwidget.h"
#import <QPainter>

ChatWidget::ChatWidget(QWidget *parent) : QWidget(parent)
{
    msg.setReadOnly(true);
    name.setReadOnly(true);
}

QSize ChatWidget::sizeHint() const
{
    return QSize(300,50);
}

void ChatWidget::paint(QPainter *painter,QFont &font, const QRect &rect, const QPalette &palette) const
{
//    painter->save();
//    painter->setClipping(true);

//    QFont f(font);
//    painter->setFont(f);
//    int width = rect.width();
//    if(avatar != ""){

//        QString path = ":/imges/" + avatar;
//        QPixmap pix(path);
//        QPixmap pix1 = pix.scaled(avatarScale, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

//        QBrush brush(pix1);
//        painter->setRenderHint(QPainter::Antialiasing);
//        painter->setBrush(brush);
//        painter->translate(QPointF(0,rect.y()));
//        painter->drawRoundedRect(QRect(QPoint(offset),avatarSize), avatarRadius, avatarRadius);
//    }
//    painter->restore();

//    painter->save();
//    QRect NameRect = rect;
//    NameRect.setHeight(baseTextHeight);
//    NameRect.setX(avatarSize.width() + textOffset);
//    NameRect.setWidth(width - rightMessageOffset);

//    painter->setFont(f);
//    painter->setPen(QColor(76,148,224));
//    painter->drawText(NameRect, Qt::TextSingleLine,
//                   item.nickname);

////    QRect TimeRect = myOpt.rect;
////    TimeRect.setHeight(baseTextHeight);
////    TimeRect.setX(45);
////    TimeRect.setWidth(width - 45);

//    QRect MessageRect = myOpt.rect;
//    MessageRect.setY(MessageRect.y() + mainMessageTopOffset);
//    MessageRect.setX(avatarSize.width() + textOffset);
//    MessageRect.setWidth(width - rightMessageOffset);

//    painter->setFont(f);
//    painter->setPen(palette.text().color());
//    painter->drawText(MessageRect, Qt::TextWrapAnywhere,
//                   QString::fromStdString(item.text));

//    painter->restore();
//    painter->save();
//    if(item.image != nullptr){

//        QFontMetrics fMetrics(option.font);
//        int height = fMetrics.boundingRect(QRect(0,0,option.widget->width() - 240,0),Qt::TextWordWrap,QString::fromStdString(item.text)).height();

//        QPixmap map = item.image->scaled(200,200,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
//        QBrush brush(map);
//        painter->setRenderHint(QPainter::Antialiasing);
//        painter->setBrush(brush);
//        painter->translate(QPoint(avatarSize.width() + textOffset,MessageRect.y()+height));
//        painter->drawRect(QRect(QPoint(0,0),map.size()));
//    }
//    painter->restore();
//    painter->save();

//     if(item.type != MessageType::OTHER_MESSAGE){
//         if(item.type == MessageType::SELF_MESSAGE_IN_PROGRESS){
//              QPixmap checkScaled = uncheck->scaled(15, 15, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
//              QBrush check(checkScaled);
//              painter->setRenderHint(QPainter::Antialiasing);
//              painter->setBrush(check);
//              painter->translate(QPointF(rect.width()-30,rect.y() + 10));
//              painter->fillRect(checkScaled.rect(),Qt::transparent);
//              painter->drawPixmap(checkScaled.rect(),checkScaled);
//         }
//         else{
//              QPixmap checkScaled = check->scaled(20, 20, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
//              QBrush check(checkScaled);
//              painter->setRenderHint(QPainter::Antialiasing);
//              painter->setBrush(check);
//              painter->translate(QPointF(rect.width()-30,rect.y() + 10));
//              painter->fillRect(checkScaled.rect(),Qt::transparent);
//              painter->drawPixmap(checkScaled.rect(),checkScaled);
//         }
//    }
//     painter->restore();
}
