#include "friendsdelegate.h"
#include <app-qt/src/models/friendsmodel.h>

friendsDelegate::friendsDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{
    avatar = new QPixmap(":/imges/standartAvatar.jpg");
}

void friendsDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    UserInf item = index.model()->data(index).value<UserInf>();
    QStyleOptionViewItem myOpt = option;
    myOpt.displayAlignment = Qt::AlignLeft;

    const QRect &rect(myOpt.rect);
    painter->save();
    painter->setClipping(true);

    const QPalette &palette(myOpt.palette);
    QFont f(myOpt.font);

    painter->fillRect(rect, myOpt.state & QStyle::State_Selected ?
                             qRgb(230,230,230) :
                             palette.light().color());
    painter->setFont(myOpt.font);
    int width = sizeHint(option,index).width();

    QFontMetrics font(f);
    QString path = ":/imges/" + QString::fromStdString(item.avatar);
    QPixmap pix(path);
    QPixmap pix1 = pix.scaled(groupIconSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    painter->save();
    QBrush brush(pix1);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(brush);
    painter->translate(QPointF(rect.topLeft() + offset));
    painter->drawRoundedRect(QRect(QPoint(0,0), groupIconSize), groupIconRadius, groupIconRadius);
    painter->restore();

    QRect GroupNameRect = myOpt.rect;
    GroupNameRect.setY(GroupNameRect.y() + textTopOffset);
    GroupNameRect.setX(groupIconSize.width() + textLeftOffset);
    GroupNameRect.setWidth(width - textRigthOffset);

    f.setBold(true);
    painter->setFont(f);
    painter->setPen(palette.text().color());
    painter->drawText(GroupNameRect, Qt::TextSingleLine,
                      font.elidedText(QString::fromStdString(item.login),Qt::ElideRight,width - textRigthOffset));


    QRect IdRect = myOpt.rect;
    IdRect.setY(IdRect.y() + textTopOffset);
    IdRect.setX(groupIconSize.width() + textLeftOffset);
    QFontMetrics fMetrics(option.font);
    int wid = fMetrics.horizontalAdvance(QString::fromStdString(item.login));
    IdRect.setX(groupIconSize.width() + textLeftOffset + wid);

    painter->setPen(QColor(120, 120, 120));
    QString log = "#" + QString::number(item.id);
    painter->drawText(IdRect,Qt::TextSingleLine,log);

    painter->setPen(palette.mid().color());
    if(rect.y() != 0)
        painter->drawLine(GroupNameRect.x(),rect.y(),rect.width(),rect.y());

    painter->restore();
}

QSize friendsDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);
    return QSize(option.widget->width() - (option.widget->contentsMargins().left() + option.widget->contentsMargins().right()),baseItemHeight);
}
