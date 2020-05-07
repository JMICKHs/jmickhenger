#ifndef MENUWIDGET_H
#define MENUWIDGET_H


#include <QWidget>
#include <QMdiArea>
#include <QSize>
#include <QPoint>
#include <QVBoxLayout>
#include <QPushButton>
#include "custommbutton/custombutton.h"
#include <QLabel>
#include <QFrame>
#include <QFocusEvent>

#include <../netlib/info/Info.h>

using namespace inf;
namespace Ui {
class MenuWidget;
}

class MenuWidget : public QFrame
{
    Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr);
     CustomButton* getCreateButton();

    ~MenuWidget();

private:
    Ui::MenuWidget *ui;

public slots:
    void setPosition();

};

#endif // MENUWIDGET_H
