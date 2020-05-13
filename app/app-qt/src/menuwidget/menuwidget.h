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
    ~MenuWidget();

private:
    Ui::MenuWidget *ui;

public slots:
    void setPosition();
    void setName(const QString &name);
    void on_nickname_rename(const QString &nick);

};

#endif // MENUWIDGET_H
