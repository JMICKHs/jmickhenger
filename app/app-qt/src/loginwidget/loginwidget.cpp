#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "netlib/AppNetwork.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    log = new QWidget(this);
    reg = new QWidget(this);
    log->setLayout(ui->mainLayout);
    reg->setLayout(ui->mainRegistrationLayout);
    this->addWidget(log);
    this->addWidget(reg);
    this->setCurrentWidget(log);
    this->resize(400,550);
    this->setMinimumSize(400,550);
    this->setMaximumSize(400,550);
    user = new UserModel;
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    auto net = AppNet::shared();
    //net->runClient([](int){});
}

void LoginWidget::login(const QString &log, const QString &password)
{
    auto net = AppNet::shared();
    net->auth(log.toStdString(),password.toStdString(),user->getAuthCallback());
}

void LoginWidget::registration(const Account &acc)
{
    auto net = AppNet::shared();
    net->registration(acc,user->getRegistrationCallback());
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_loginButton_clicked()
{

}

void LoginWidget::on_RegistrationButton_clicked()
{
  this->setCurrentWidget(reg);
}
