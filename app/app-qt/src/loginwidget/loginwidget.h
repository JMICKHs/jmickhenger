#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <netlib/info/Info.h>
#include <app-qt/src/models/usermodel.h>
using namespace inf;

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    void login(const QString &log,const QString &password);
    ~LoginWidget();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginWidget *ui;
    UserModel *user;
};

#endif // LOGINWIDGET_H
