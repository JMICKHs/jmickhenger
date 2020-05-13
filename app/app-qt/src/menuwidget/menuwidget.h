#ifndef MENUWIDGET_H
#define MENUWIDGET_H


#include <QWidget>
#include "app-qt/src/custommbutton/custombutton.h"
#include <QFrame>
#include <netlib/info/Info.h>

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
