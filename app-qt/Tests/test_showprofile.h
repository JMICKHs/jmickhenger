#ifndef TEST_SHOWPROFILE_H
#define TEST_SHOWPROFILE_H

#include <QtTest>
#include "../mainwindow.h"

class test_ShowProfile : public MainWindow
{
    Q_OBJECT

public:
    test_ShowProfile();
    ~test_ShowProfile();



private slots:
    void test_ShowProfile1();
};

#endif // TEST_SHOWPROFILE_H
