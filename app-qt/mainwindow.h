#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "grouplistobject.h"
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


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void linkObjects();
    void createObjects();
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    ChatList &getChatList();

public slots:
    void menuClicked();
    void messageButtonClicked();

signals:
    void sendMessage(const Message&);

protected:
    MenuWidget *menuWidget;
    QHBoxLayout *mainHLayout;
    QVBoxLayout *firstVLayout;
    QVBoxLayout *secondVLayout;
    QHBoxLayout *searchHLayout;
    QHBoxLayout *topHLayout;
    QHBoxLayout *bottomHLayout;

    QSplitter *splitter;

    GroupListObject *listObject;
    ChatList *chatList;

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
