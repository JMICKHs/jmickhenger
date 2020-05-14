#ifndef MENUWIDGET_H
#define MENUWIDGET_H


#include <QWidget>
#include "app-qt/src/custommbutton/custombutton.h"
#include <QFrame>
#include <netlib/info/Info.h>
#include <app-qt/src/creategroup/creategroupwidget.h>

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
    CreateGroupWidget* getCreateWidget();
private:
    Ui::MenuWidget *ui;
    std::shared_ptr<CreateGroupWidget> friendsWidget;
public slots:
    void setPosition();
    void setName(const QString &name);
    void on_nickname_rename(const QString &nick);

private slots:
    void on_createGroupButton_clicked();
    void on_contactsButton_clicked();
};

#endif // MENUWIDGET_H
