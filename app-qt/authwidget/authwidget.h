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
    std::function<void(const UserInfo& user)> getChatCallback;
    std::function<void(const int& id)> registrationCallback;

public:
    AuthWidget(QWidget *parent = nullptr);
    void registration();
    void login(QString number,QString password);
    void saveInChache(const bool&state);
    int getId() const;
};

#endif // AUTHWIDGET_H
