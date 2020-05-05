#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFrame>
#include <QSplitter>
#include <QResizeEvent>
#include <QMoveEvent>
#include <QLabel>
#include "custommbutton/CustomButton.h"
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

class AppNetwork;

namespace Ui {
    class  mainwindowform;
}
class MainWindow : public QWidget
{
    Q_OBJECT

private:
    void createObjects();
    void linkObjects();
    void getChats();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;

    ChatList &getChatList();
    GroupList &getGroupList();

    void createMessage(const Message& message);
    void addProfileData(const ProfileData &data);

    AppNetwork *client;

public slots:
    void menuClicked();
    void messageButtonClicked();
    void searchById(int id);

signals:
    void sendMessage(const Message&);
    void sendData(const ProfileData&);

protected:

    std::vector<ProfileData> profileData;
    MenuWidget *menuWidget;
    DataShowWidget *dataShow;

    QVBoxLayout *firstVLayout;
    QVBoxLayout *secondVLayout;
    QHBoxLayout *mainHLayout;
    QHBoxLayout *searchHLayout;
    QHBoxLayout *topHLayout;
    QHBoxLayout *bottomHLayout;

    QSplitter *splitter;

    GroupList *listObject;
    ChatList *chatList;
    AuthWidget *auth;

    CustomButton *menu;
    QLineEdit *search;

    QWidget *leftSide;
    QWidget *rightSide;

    QLabel *groupName;
    CustomButton *groupSearch;
    CustomButton *groupActions;

    CustomButton *inputFiles;
    CustomButton *send;
    QLineEdit *textMessage;

    GroupListView *groupView;
    GroupModel *groupModel;
    ChatModel *chatModel;
    ChatView *chatView;

    Ui::mainwindowform *ui;

};
#endif // MAINWINDOW_H
