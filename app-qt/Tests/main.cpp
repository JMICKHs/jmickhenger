#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "test_chat.h"
#include "test_group.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTest::qExec(new test_chat(), argc, argv);
    QTest::qExec(new test_group(), argc, argv);
    return 0;
}
