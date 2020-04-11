#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "test_chat.h"

using namespace std;

int main(int argc, char *argv[])
{
    freopen("testing.log", "w", stdout);
    QApplication a(argc, argv);
    QTest::qExec(new test_chat(), argc, argv);
    cout << endl;
    return 0;
}
