#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFrame>
#include "chatlist.h"
#include <QSplitter>
#include <QResizeEvent>
#include <QMoveEvent>
#include <QLabel>
#include "CustomButton.h"
#include "menuwidget.h"
#include "profiledata.h"
#include "datashowwidget.h"
#include "authwidget.h"

class AppNetwork;

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

    AppNetwork *client;
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

};
#endif // MAINWINDOW_H
