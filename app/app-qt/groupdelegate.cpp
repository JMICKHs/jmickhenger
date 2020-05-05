#include "groupdelegate.h"
#include <QDebug>


GroupDelegate::GroupDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void GroupDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    GroupItem item = index.model()->data(index).value<GroupItem>();
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

    QRect GroupNameRect = myOpt.rect;
    GroupNameRect.setX(45);
    GroupNameRect.setWidth(width - 130);

    painter->setFont(f);
    painter->setPen(palette.text().color());
    painter->drawText(GroupNameRect, Qt::TextSingleLine,
                      font.elidedText(item.name,Qt::ElideRight,width - 130));


    QRect LastMessageRect = QRect(45,GroupNameRect.y() + 35,width - 130,30);
    painter->setFont(f);
    painter->setPen(palette.text().color());
    painter->drawText(LastMessageRect, Qt::TextSingleLine,
                      font.elidedText(item.lastMessage,Qt::ElideRight,width - 130));

    QRect TimeMessageRect = QRect(width - 45 - 20 ,GroupNameRect.y() + 5,20,30);
    painter->setFont(f);
    painter->setPen(palette.text().color());
    painter->drawText(TimeMessageRect, Qt::TextSingleLine,
                      item.time);

    painter->restore();
}

QSize GroupDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);
    return QSize(option.widget->width() - (option.widget->contentsMargins().left() + option.widget->contentsMargins().right()),55);
}
