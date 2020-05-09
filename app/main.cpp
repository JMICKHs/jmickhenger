#include "app-qt/src/mainwidget/mainwidget.h"
#include <QApplication>
#include "app-qt/src/loginwidget/loginwidget.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWidget w;
    w.show();
    LoginWidget lg;
    lg.show();
    return a.exec();
}
