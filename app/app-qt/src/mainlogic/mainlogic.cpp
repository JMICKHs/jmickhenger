#include "mainlogic.h"
#include "netlib/AppNetwork.h"
#include "app-qt/src/models/usermodel.h"
#include <QDebug>

MainLogic::MainLogic()
{
}

void MainLogic::runApp()
{
    lgWidget = new LoginWidget;
    mainWidget = new MainWidget;
    auto appNet = AppNet::shared();
    auto acc = appNet->accFromCache();
    appNet->runClient([](int){});
    if(acc){

        appNet->auth(acc->login,acc->password,UserModel::instance()->getAuthWithCacheCallback());
    }
    else{
        lgWidget->show();
    }
    mainWidget->resize(880,550);
    connect(mainWidget->getMenu(),&MenuWidget::closeAndExit,lgWidget,&LoginWidget::show);
    connect(mainWidget->getMenu(),&MenuWidget::closeAndExit,mainWidget,&MainWidget::close);
    connect(lgWidget,&LoginWidget::openMainWidget,mainWidget,&MainWidget::after_Login_slot);

}
