#ifndef FRIENDSDELEGATE_H
#define FRIENDSDELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>

class friendsDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit friendsDelegate(QObject*parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index ) const override;
private:
    QPixmap *avatar;
    QPoint offset{5,5};
    int textLeftOffset{15};
    int textTopOffset{5};
    int baseTextHeigth{15};
    int textRigthOffset{150};
    int baseItemHeight{60};
    QSize groupIconSize{50,50};
    int groupIconRadius{100};
};

#endif // FRIENDSDELEGATE_H
