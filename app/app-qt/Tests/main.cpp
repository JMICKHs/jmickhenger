#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "test_chat.h"
#include "test_group.h"
#include "test_showprofile.h"
#include "gtest/gtest.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); 
    QTest::qExec(new test_chat(), argc, argv);
    QTest::qExec(new test_showprofile(), argc, argv);
    QTest::qExec(new test_group(), argc, argv);
    ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS( );
}
