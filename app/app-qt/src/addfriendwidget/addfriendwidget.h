#ifndef ADDFRIENDWIDGET_H
#define ADDFRIENDWIDGET_H

#include <QWidget>

namespace Ui {
class addFriendWidget;
}

class addFriendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit addFriendWidget(QWidget *parent = nullptr);
    ~addFriendWidget();

private slots:
    void on_addFriendButton_clicked();
signals:
    void friendAddSignal(int id);

private:
    Ui::addFriendWidget *ui;
};

#endif // ADDFRIENDWIDGET_H
