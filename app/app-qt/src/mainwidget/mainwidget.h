#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "app-qt/src/custommbutton/custombutton.h"
#include "app-qt/src/menuwidget/menuwidget.h"
#include <app-qt/src/models/groupmodel.h>
#include <app-qt/src/views/grouplistview.h>
#include <app-qt/src/delegates/groupdelegate.h>
#include <app-qt/src/models/chatmodel.h>
#include <app-qt/src/views/chatview.h>
#include <app-qt/src/delegates/chatdelegate.h>
#include <app-qt/src/proxy/proxymodel.h>
#include <app-qt/src/models/usermodel.h>
#include <QFocusEvent>
#include <QAction>
#include <QMenu>

enum class Buttons{
    SEND_MESSAGE_BUTTON,
    MENU_BUTTON,
    GROUP_BUTTON,
};

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

public slots:
    void menuClicked();
    void sendMessageFromInput();
    void after_Login_slot();
    void removeMessageFromChat();
    void editMessageInChat();
    void showContextMenu(const QPoint &pos);

signals:
    void sendMessageFromInput_s(const Message &message);
private:
    Ui::MainWidget *ui;
    void removeDoubleEnter(QString &str);

protected:
    std::shared_ptr<GroupModel> groupModel;
    std::shared_ptr<ChatModel> chatModel;
    MenuWidget *menuWidget;
    QMenu *msgMenu;
    ProxyModel *proxyModel;

private slots:
    void on_groupList_clicked(const QModelIndex &index);
};

#endif // MAINWIDGET_H
