#ifndef CHATDELEGATE_H
#define CHATDELEGATE_H


#include <QItemDelegate>
#include "app-qt/src/models/chatmodel.h"
#include <QPainter>
#include <QStyledItemDelegate>
#include <QRect>

class ChatDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ChatDelegate(QObject *parent = 0);   
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index ) const override;   
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,  const QModelIndex &index) override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                  const QModelIndex &index) const override;

private:
    QPixmap *avatar;
    QPixmap *check;
    QPixmap *uncheck;
};


#endif // CHATDELEGATE_H
