#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QLineEdit>
#include <netlib/info/Info.h>
#include <app-qt/src/models/usermodel.h>
using namespace inf;

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    void login(const QString &log,const QString &password);
    void registration(const Account &acc);
    ~LoginWidget();

private slots:
    void on_loginButton_clicked();

    void on_RegistrationButton_clicked();

private:
    Ui::LoginWidget *ui;
    QWidget *log;
    QWidget *reg;
    UserModel *user;
};

#endif // LOGINWIDGET_H
