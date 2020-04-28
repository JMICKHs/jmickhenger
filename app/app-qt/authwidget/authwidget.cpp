#include "authwidget.h"

AuthWidget::AuthWidget(QWidget *parent)
    : QWidget(parent)
{
    number =  new QLineEdit;
    password  = new QLineEdit;
    userCallback = [](const UserInfo user){};
    registrationCallback = [](const int id){};
}

std::function<void (const UserInfo user)> AuthWidget::getUserCallback()
{
    return userCallback;
}

std::function<void (const int id)> AuthWidget::getRegistationCallback()
{
    return registrationCallback;
}

void AuthWidget::registration()
{

}

void AuthWidget::login(QString number, QString password)
{

}

int AuthWidget::getId() const
{
  return id;
}


