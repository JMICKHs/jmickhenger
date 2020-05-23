#ifndef MENUWIDGET_H
#define MENUWIDGET_H


#include <QWidget>
#include "app-qt/src/custommbutton/custombutton.h"
#include <QFrame>
#include <netlib/info/Info.h>
#include <app-qt/src/creategroup/creategroupwidget.h>
#include <app-qt/src/setavatarwidget/setavatarwidget.h>


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
    SetAvatarWidget *avatWidget;
    std::shared_ptr<CreateGroupWidget> friendsWidget;

signals:
    void getListFriendSignal();
    void closeAndExit();
public slots:
    void setPosition();
    void setName(const QString &name);
    void on_nickname_rename(const QString &nick);
    void on_image_change(const QString &str);
private slots:
    void on_createGroupButton_clicked();
    void on_contactsButton_clicked();
    void on_pushButton_clicked();
    void on_exitButton_clicked();
};

#endif // MENUWIDGET_H
