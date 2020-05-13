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
    QPoint offset{5,5};
    int textOffset{15};
    int mainMessageTopOffset{15};
    int baseItemHeight{55};
    int rightMessageOffset{80};
    int avatarRadius{100};
    float baseTextHeight{15};
    QSize avatarSize{30,30};
    QSize avatarScale{40,40};
};


#endif // CHATDELEGATE_H
