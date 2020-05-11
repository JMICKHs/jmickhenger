#include "app-qt/src/mainwidget/mainwidget.h"
#include <QApplication>
#include "app-qt/src/loginwidget/loginwidget.h"
#include <QObject>
#include "app-qt/src/mainlogic/mainlogic.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainLogic app;
    return a.exec();
}
