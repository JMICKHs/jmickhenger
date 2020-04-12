#ifndef TEST_GROUP_H
#define TEST_GROUP_H

#include <QtTest>
#include "../mainwindow.h"

class test_group : public  MainWindow
{
    Q_OBJECT

public:
    test_group();
    ~test_group();



private slots:
    void test_gr1();


};

#endif // TEST_GROUP_H
