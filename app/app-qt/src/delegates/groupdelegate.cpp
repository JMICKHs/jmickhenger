#include "groupdelegate.h"
#include <QDebug>
#include <netlib/info/Info.h>

GroupDelegate::GroupDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    groupIcon =  new QPixmap("/home/kostikan/jmickhenger/app/img/standartAvatar.jpg");
}

void GroupDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Chat item = index.model()->data(index).value<Chat>();
    QStyleOptionViewItem myOpt = option;
    myOpt.displayAlignment = Qt::AlignLeft;

    const QRect &rect(myOpt.rect);
    painter->save();
    painter->setClipping(true);

    const QPalette &palette(myOpt.palette);
    QFont f(myOpt.font);

    painter->fillRect(rect, myOpt.state & QStyle::State_Selected ?
                             palette.highlight().color() :
                             palette.light().color());
    painter->setFont(myOpt.font);

    int width = sizeHint(option,index).width();

    QFontMetrics font(f);

    QPointF groupIconSize{50,50};

    QPixmap scaled = groupIcon->scaled(groupIconSize.x(), groupIconSize.y(),
                                       Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    painter->save();
    QBrush brush(scaled);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(brush);
    painter->translate(QPointF(5,rect.y() + 5));
    painter->drawRoundedRect(0, 0, groupIconSize.x(), groupIconSize.y(), 100, 100);
    painter->restore();

    QRect GroupNameRect = myOpt.rect;
    GroupNameRect.setX(groupIconSize.x() + 15);
    GroupNameRect.setWidth(width - 130);

    painter->setFont(f);
    painter->setPen(palette.text().color());
    painter->drawText(GroupNameRect, Qt::TextSingleLine,
                      font.elidedText(QString::fromStdString(item.chat.name),Qt::ElideRight,width - 150));


    QRect LastMessageRect = QRect(groupIconSize.x() + 15,GroupNameRect.y() + 35,width - 130,30);
    painter->setFont(f);
    painter->setPen(palette.text().color());
   // painter->drawText(LastMessageRect, Qt::TextSingleLine,
     //                 font.elidedText(item.lastMessage,Qt::ElideRight,width - 150));


    //if(sizeHint(option,index).width() > 140){
    //    QRect TimeMessageRect = QRect(width - groupIconSize.x() - 20 ,GroupNameRect.y() + 5,40,30);
    //    painter->setFont(f);
    //    painter->setPen(palette.text().color());
    //    painter->drawText(TimeMessageRect, Qt::TextSingleLine,
    //                  item.time);
    //}
    painter->setPen(palette.mid().color());
    if(rect.y() != 0)
        painter->drawLine(GroupNameRect.x(),rect.y(),rect.width(),rect.y());

    painter->restore();
}

QSize GroupDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);
    return QSize(option.widget->width() - (option.widget->contentsMargins().left() + option.widget->contentsMargins().right()),60);
}
