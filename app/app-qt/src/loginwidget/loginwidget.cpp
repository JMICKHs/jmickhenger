#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "netlib/AppNetwork.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    this->setLayout(ui->mainLayout);
    user = new UserModel;
    auto net = AppNet::shared();
    //net->runClient([](int){});
}

void LoginWidget::login(const QString &log, const QString &password)
{
    auto net = AppNet::shared();
    //net->auth(log.toStdString(),password.toStdString(),user->getAuthCallback());
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_loginButton_clicked()
{

}
