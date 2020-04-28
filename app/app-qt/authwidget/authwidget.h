#ifndef AUTHWIDGET_H
#define AUTHWIDGET_H

#include <QWidget>
#include <QLineEdit>
struct UserInfo
{
};

class AuthWidget : public QWidget
{
    Q_OBJECT

private:
    bool state;
    QLineEdit *number;
    QLineEdit *password;
    int id;

    std::function<void(const UserInfo user)> userCallback;
    std::function<void(const int id)> registrationCallback;

public:
    AuthWidget(QWidget *parent = nullptr);

    void registration();
    void login(QString number,QString password);
    int getId() const;

    std::function<void(const UserInfo user)> getUserCallback();
    std::function<void(const int id)> getRegistationCallback();
};

#endif // AUTHWIDGET_H
