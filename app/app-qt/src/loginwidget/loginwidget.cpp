#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "netlib/AppNetwork.h"
#include <QStyle>
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    log = new QWidget(this);
    reg = new QWidget(this);
    connect(user,&UserModel::showMainWidget,this,&LoginWidget::showMainWidgetSlot);
    connect(user,&UserModel::showMainWidget,this,&LoginWidget::close);
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
    net->runClient([](int){});
}

void LoginWidget::login(const QString &log, const QString &password)
{
    auto net = AppNet::shared();
    qDebug() <<"log";
    net->auth(log.toStdString(),password.toStdString(),user->getAuthCallback());
}

void LoginWidget::registration(const Account &acc)
{
    auto net = AppNet::shared();
    qDebug() <<"reg";
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
  login(ui->loginButton->text(),ui->passwordInput->text());
  this->setCurrentWidget(reg);
}

void LoginWidget::on_returnButton_clicked()
{
  this->setCurrentWidget(log);
}

void LoginWidget::on_registrateButton_clicked()
{
    Account acc;
    acc.login = ui->loginRegInput->text().toStdString();
    acc.password = ui->fPassRegInput->text().toStdString();
    this->registration(acc);

}

void LoginWidget::showMainWidgetSlot()
{
    emit openMainWidget();
}
