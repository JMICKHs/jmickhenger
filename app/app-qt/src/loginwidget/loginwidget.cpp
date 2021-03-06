#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "netlib/AppNetwork.h"
#include <QStyle>
#include <QDir>
#include <QDebug>
#include <QMovie>

LoginWidget::LoginWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    log = new QWidget(this);
    this->setWindowTitle("Jmicknger");
    reg = new QWidget(this);

    log->setLayout(ui->mainLayout);
    reg->setLayout(ui->mainRegistrationLayout);
    this->addWidget(log);
    this->addWidget(reg);
    this->setCurrentWidget(log);
    this->resize(400,550);
    this->setMinimumSize(400,550);
    this->setMaximumSize(400,550);
    UserModel::instance()->setCallBacks();
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    ui->avatarButton->setFlat(true);
    ui->avatarButton->setFixedSize(70,70);
    QPixmap pix1(":/imges/standartAvatar.jpg");
    this->path = "standartAvatar.jpg";
    QPixmap pix(pix1.scaled(55,55, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    QPalette palette;
    palette.setBrush(ui->avatarButton->backgroundRole(), QBrush(pix));
    ui->avatarButton->setAutoFillBackground(true);
    ui->avatarButton->setPalette(palette);
    QRect rect(0,0,55,55);
    QRegion region(rect, QRegion::Ellipse);
    ui->avatarButton->setMask(region);

    connect(UserModel::instance(),&UserModel::showMainWidget,this,&LoginWidget::showMainWidgetSlot);
    connect(UserModel::instance(),&UserModel::showMainWidget,this,&LoginWidget::close);
    avatarWidget = new SetAvatarWidget(this);
    connect(avatarWidget,&SetAvatarWidget::avatarChangeSignal,this,&LoginWidget::avatarChange);
    QMovie *movie = new QMovie(":/imges/ZKZg.gif");
    movie->setScaledSize(QSize(40,40));
    ui->loadAnimation->setFixedSize(QSize(40,40));
    ui->loadAnimation_2->setFixedSize(QSize(40,40));
    ui->loadAnimation->setMovie(movie);
    ui->loadAnimation_2->setMovie(movie);
    connect(UserModel::instance(),&UserModel::stopAnimationSignal,this,&LoginWidget::stopAnimation);
    connect(UserModel::instance(),&UserModel::upFlag,this,&LoginWidget::upProtectedFlag);

    ui->labelInfoLogin->setStyleSheet("color: rgb(200, 0, 0)");
    ui->infoRegister->setStyleSheet("color: rgb(200, 0, 0)");
    ui->labelInfoLogin->setWordWrap(true);
    ui->infoRegister->setWordWrap(true);
    ui->labelInfoLogin->setAlignment(Qt::AlignHCenter);
    ui->infoRegister->setAlignment(Qt::AlignHCenter);
    connect(UserModel::instance(),&UserModel::setLogInfo,this,&LoginWidget::changeLogInfo);
    connect(UserModel::instance(),&UserModel::setRegInfo,this,&LoginWidget::changeRegInfo);
}

void LoginWidget::login(const QString &log, const QString &password)
{
    auto net = AppNet::shared();
    qDebug() <<"log";
    net->auth(log.toStdString(),password.toStdString(),UserModel::instance()->getAuthCallback());
    stopDoubleTapOnRegistrateOrLogin = true;
    ui->loginInput->clear();
    ui->passwordInput->clear();
}

void LoginWidget::registration(const Account &acc)
{
    auto net = AppNet::shared();
    qDebug() <<"reg" << QString::fromStdString(acc.login) << QString::fromStdString(acc.password);
    UserModel::instance()->setLogin(acc.login);
    UserModel::instance()->setPassword(acc.password);
    UserModel::instance()->setAvatar(path);
    net->registration(acc,UserModel::instance()->getRegistrationCallback());
    stopDoubleTapOnRegistrateOrLogin = true;
    ui->loginRegInput->clear();
    ui->fPassRegInput->clear();
    ui->sPassRegInput->clear();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_loginButton_clicked()
{
    if(stopDoubleTapOnRegistrateOrLogin){
        return;
    }
    ui->loadAnimation->show();
    ui->loadAnimation->movie()->start();
    login(ui->loginInput->text(),ui->passwordInput->text());

}

void LoginWidget::on_RegistrationButton_clicked()
{
     ui->labelInfoLogin->clear();
     this->setCurrentWidget(reg);
}

void LoginWidget::on_returnButton_clicked()
{
    this->setCurrentWidget(log);
}

void LoginWidget::on_registrateButton_clicked()
{
    ui->infoRegister->clear();
    if(stopDoubleTapOnRegistrateOrLogin){
        return;
    }
    ui->loadAnimation_2->show();
    ui->loadAnimation_2->movie()->start();
    Account acc;
    acc.login = ui->loginRegInput->text().toStdString();
    acc.password = ui->fPassRegInput->text().toStdString();
    acc.avatar = path.toStdString();
    this->registration(acc);
}

void LoginWidget::on_avatarButton_clicked()
{
    avatarWidget->show();
    avatarWidget->move(pos().x() + size().width()/(4),
               pos().y() + size().height()/(4));

}

void LoginWidget::avatarChange(const QString &path)
{
    QString name = ":/imges/" + path;
    QPixmap pix1(name);
    QPixmap pix(pix1.scaled(55,55, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    QPalette palette;
    palette.setBrush(ui->avatarButton->backgroundRole(), QBrush(pix));
    ui->avatarButton->setAutoFillBackground(true);
    ui->avatarButton->setPalette(palette);
    this->path = path;
}

void LoginWidget::showMainWidgetSlot()
{
    emit openMainWidget();
}

void LoginWidget::stopAnimation()
{
     ui->loadAnimation->movie()->stop();
     ui->loadAnimation_2->movie()->stop();
     ui->loadAnimation->hide();
     ui->loadAnimation_2->hide();
}

void LoginWidget::upProtectedFlag(bool flag)
{
    stopDoubleTapOnRegistrateOrLogin = flag;
}

void LoginWidget::changeRegInfo(const QString &str)
{
    ui->infoRegister->setText(str);
    ui->infoRegister->adjustSize();
    ui->infoRegister->show();
}

void LoginWidget::changeLogInfo(const QString &str)
{
    ui->labelInfoLogin->setText(str);
    ui->labelInfoLogin->adjustSize();
    ui->labelInfoLogin->show();
}


