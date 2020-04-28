#ifndef TEST_SHOWPROFILE_H
#define TEST_SHOWPROFILE_H

#include <QtTest>
#include "../mainwindow/mainwindow.h"

class test_showprofile : public MainWindow
{
    Q_OBJECT

public:
    test_showprofile();
    ~test_showprofile();



private slots:
    void test_ShowProfile1();
    void test_ShowProfile2();
};

#endif // TEST_SHOWPROFILE_H
