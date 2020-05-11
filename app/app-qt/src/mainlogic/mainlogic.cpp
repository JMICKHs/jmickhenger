#include "mainlogic.h"

MainLogic::MainLogic()
{
    lgWidget = new LoginWidget;
    mainWidget = new MainWidget;
    lgWidget->show();
    connect(lgWidget,&LoginWidget::openMainWidget,mainWidget,&MainWidget::show);
}
