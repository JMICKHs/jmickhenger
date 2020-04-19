#ifndef MENUWIDGET_H
#define MENUWIDGET_H


#include <QWidget>
#include <QMdiArea>
#include <QSize>
#include <QPoint>
#include <QVBoxLayout>
#include <QPushButton>
#include "custommbutton/CustomButton.h"
#include <QLabel>
#include <QFrame>
#include "grouplist/grouplist.h"

class MenuWidget : public QFrame
{
    Q_OBJECT
private:
    QVBoxLayout *vLayout;
    CustomButton *settings;
    CustomButton *createGroup;
    CustomButton *friends;
    CustomButton *avatar;

    QLabel *label;
    QVBoxLayout *topLayout;
    QWidget *topWidget;

    int Id;
    float height;

public:
    explicit MenuWidget(QFrame *parent = nullptr, const QSize size = QSize());
    CustomButton* getCreateButton();

public slots:
    void setPosition();

signals:
    void createGroupSignal(Chat &chat);
};

#endif // MENUWIDGET_H
