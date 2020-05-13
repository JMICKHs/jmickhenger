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

    log->setLayout(ui->mainLayout);
    reg->setLayout(ui->mainRegistrationLayout);
    this->addWidget(log);
    this->addWidget(reg);
    this->setCurrentWidget(log);
    this->resize(400,550);
    this->setMinimumSize(400,550);
    this->setMaximumSize(400,550);
    userPtr = std::make_shared<UserModel>();
    userPtr->setCallBacks();
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    auto net = AppNet::shared();
    net->runClient([](int){});
    connect(userPtr.get(),&UserModel::showMainWidget,this,&LoginWidget::showMainWidgetSlot);
    connect(userPtr.get(),&UserModel::showMainWidget,this,&LoginWidget::close);
}

void LoginWidget::login(const QString &log, const QString &password)
{
    auto net = AppNet::shared();
    qDebug() <<"log";
    net->auth(log.toStdString(),password.toStdString(),userPtr->getAuthCallback());

}

void LoginWidget::registration(const Account &acc)
{
    auto net = AppNet::shared();
    qDebug() <<"reg" << QString::fromStdString(acc.login) << QString::fromStdString(acc.password);
    userPtr->setLogin(acc.login);
    userPtr->setPassword(acc.password);
    net->registration(acc,userPtr->getRegistrationCallback());
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_loginButton_clicked()
{
     login(ui->loginInput->text(),ui->passwordInput->text());
}

void LoginWidget::on_RegistrationButton_clicked()
{
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
    emit openMainWidget(userPtr);
}
