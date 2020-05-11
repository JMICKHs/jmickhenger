#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFrame>
#include <QSplitter>
#include <QResizeEvent>
#include <QMoveEvent>
#include <QLabel>
#include "app-qt/src/custommbutton/custombutton.h"
#include "app-qt/src/menuwidget/menuwidget.h"
#include "app-qt/src/profiledata/profiledata.h"
#include "app-qt/src/datashowwidget/datashowwidget.h"
#include "app-qt/src/authwidget/authwidget.h"
#include "app-qt/src/chatlist/chatlist.h"
#include <QListView>
#include <app-qt/src/models/groupmodel.h>
#include <app-qt/src/views/grouplistview.h>
#include <app-qt/src/delegates/groupdelegate.h>
#include <app-qt/src/models/chatmodel.h>
#include <app-qt/src/views/chatview.h>
#include <app-qt/src/delegates/chatdelegate.h>
#include <app-qt/src/proxy/proxymodel.h>
#include <QFocusEvent>
#include <memory>

class AppNetwork;

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

public slots:
    void menuClicked();
    void sendMessageFromInput();
    void after_Login_slot();

signals:
    void sendMessageFromInput_s(const Message &message);
private:
    Ui::MainWidget *ui;
    void removeDoubleEnter(QString &str);

protected:
    std::shared_ptr<GroupModel> groupModel;
    std::shared_ptr<ChatModel> chatModel;
    MenuWidget *menuWidget;
    AppNetwork *network;
    ProxyModel *proxyModel;
private slots:
    void on_groupList_clicked(const QModelIndex &index);
    void on_searchInput_textChanged(const QString &arg1);
};

#endif // MAINWIDGET_H
