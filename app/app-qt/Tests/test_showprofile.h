#ifndef TEST_SHOWPROFILE_H
#define TEST_SHOWPROFILE_H

#include <QtTest/QtTest>
#include "app-qt/src/mainwidget/mainwidget.h"

class test_showprofile : public MainWidget
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
