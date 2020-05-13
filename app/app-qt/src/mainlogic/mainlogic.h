#ifndef MAINLOGIC_H
#define MAINLOGIC_H

#include "app-qt/src/mainwidget/mainwidget.h"
#include <QApplication>
#include "app-qt/src/loginwidget/loginwidget.h"

class MainLogic : public QObject
{
    Q_OBJECT
public:
    MainLogic();
    void runApp();
private:
    LoginWidget *lgWidget;
    MainWidget *mainWidget;
};

#endif // MAINLOGIC_H
