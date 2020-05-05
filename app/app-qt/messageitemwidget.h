#ifndef MESSAGEITEMWIDGET_H
#define MESSAGEITEMWIDGET_H

#include <QWidget>

namespace Ui {
class MessageItemWidget;
}

class MessageItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageItemWidget(QWidget *parent = nullptr);
   MessageItemWidget(const QModelIndex & index, QWidget * parent);

    ~MessageItemWidget();
   void setTest(const QString &message);

private:
    Ui::MessageItemWidget *ui;
};

#endif // MESSAGEITEMWIDGET_H
