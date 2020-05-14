#ifndef CREATEGROUPWIDGET_H
#define CREATEGROUPWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <memory>
#include <app-qt/src/models/groupmodel.h>
#include <app-qt/src/models/usermodel.h>
#include <app-qt/src/models/friendsmodel.h>

namespace Ui {
class CreateGroupWidget;
}
enum class WidgetType{
    CREATE_GROUP,
    CONTACTS
};

class CreateGroupWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit CreateGroupWidget(QWidget *parent = nullptr);
    ~CreateGroupWidget();
    void setWidget(WidgetType type);

private:
    Ui::CreateGroupWidget *ui;
    QWidget *createWidget;
    QWidget *contactsWidget;
    std::shared_ptr<FriendsModel> friendModel;
};

#endif // CREATEGROUPWIDGET_H
