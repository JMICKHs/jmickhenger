#ifndef CHATDELEGATE_H
#define CHATDELEGATE_H

#include "app-qt/src/models/chatmodel.h"
#include <QStyledItemDelegate>
#include <QTextEdit>
#include <QPainter>

class ChatDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ChatDelegate(QWidget *parent = 0);
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index ) const override;   
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,  const QModelIndex &index) override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                  const QModelIndex &index) const override;
    void setEditorData(QWidget* editor, const QModelIndex &index) const override;
    QWidget* createEditor(QWidget* parent,const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QWidget showPicture;
    QPixmap *avatar;
    QPixmap *check;
    QPixmap *uncheck;
    QPoint offset{5,5};
    int textOffset{15};
    int mainMessageTopOffset{14};
    int baseItemHeight{50};
    int rightMessageOffset{80};
    int avatarRadius{100};
    float baseTextHeight{15};
    QSize avatarSize{35,35};
    QSize avatarScale{45,45};
};


#endif // CHATDELEGATE_H
