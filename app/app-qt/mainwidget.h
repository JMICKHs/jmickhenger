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
#include "custommbutton/custombutton.h"
#include "menuwidget.h"
#include "profiledata/profiledata.h"
#include "datashowwidget/datashowwidget.h"
#include "authwidget/authwidget.h"
#include "chatlist/chatlist.h"
#include <QListView>
#include <groupmodel.h>
#include <grouplistview.h>
#include <groupdelegate.h>
#include <chatmodel.h>
#include <chatview.h>
#include <chatdelegate.h>
#include "proxymodel.h"
#include <../netlib/AppNetwork.h>
#include <QFocusEvent>

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

signals:
    void sendMessageFromInput_s(const Message &message);
private:
    Ui::MainWidget *ui;
    void removeDoubleEnter(QString &str);

protected:
    GroupModel *groupModel;
    ChatModel *chatModel;
    MenuWidget *menuWidget;
    AppNetwork *network;
    ProxyModel *proxyModel;
private slots:
    void on_groupList_clicked(const QModelIndex &index);
    void on_searchInput_textChanged(const QString &arg1);
};

#endif // MAINWIDGET_H
