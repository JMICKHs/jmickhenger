#ifndef TEST_CHAT_H
#define TEST_CHAT_H

#include <QtTest>
#include "../mainwindow/mainwindow.h"



class test_chat : public MainWindow
{
    Q_OBJECT

public:
    test_chat();
    ~test_chat();



private slots:
    void test_case1();
    void test_case2();
    void test_case3();

};

#endif // TEST_CHAT_H
