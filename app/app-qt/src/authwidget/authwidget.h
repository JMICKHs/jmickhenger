#ifndef AUTHWIDGET_H
#define AUTHWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <netlib/info/Info.h>
#include <app-qt/src/models/usermodel.h>
using namespace inf;

class AuthWidget : public QWidget
{
    Q_OBJECT

private:
    UserModel *user;
    bool state;
    QLineEdit *number;
    QLineEdit *password;
    int id;

public:
    AuthWidget(QWidget *parent = nullptr);

    void registration();
    void login(const QString &number,const QString &password);
};

#endif // AUTHWIDGET_H
