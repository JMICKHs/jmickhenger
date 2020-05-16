#include "mainlogic.h"

MainLogic::MainLogic()
{
}

void MainLogic::runApp()
{
    lgWidget = new LoginWidget;
    mainWidget = new MainWidget;
    lgWidget->show();
    mainWidget->show();
    connect(lgWidget,&LoginWidget::openMainWidget,mainWidget,&MainWidget::after_Login_slot);
}
