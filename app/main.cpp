#include <QApplication>
#include "app-qt/src/mainlogic/mainlogic.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainLogic app;
    app.runApp();
    return a.exec();
}
