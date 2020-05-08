#ifndef GROUPDELEGATE_H
#define GROUPDELEGATE_H

#include <QItemDelegate>
#include "app-qt/src/models/groupmodel.h"
#include <QPainter>
#include <QStyledItemDelegate>

class GroupDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit GroupDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index ) const override;
private:
    QPixmap *groupIcon;
};

#endif // GROUPDELEGATE_H
