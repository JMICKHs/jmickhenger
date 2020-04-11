#ifndef MENUWIDGET_H
#define MENUWIDGET_H


#include <QWidget>
#include <QMdiArea>
#include <QSize>
#include <QPoint>
#include <QVBoxLayout>
#include <QPushButton>
#include "CustomButton.h"
#include <QLabel>
#include <QFrame>

class MenuWidget : public QFrame
{
    Q_OBJECT
private:
    QVBoxLayout *vLayout;
    CustomButton *settings;
    CustomButton *createGroup;
    CustomButton *friends;
    QLabel *label;
    CustomButton *avatar;
    QVBoxLayout *topLayout;
    QWidget *topWidget;

    float height;
public:
    explicit MenuWidget(QFrame *parent = nullptr, const QSize size = QSize());
public slots:
    void setPosition();
};

#endif // MENUWIDGET_H
