#include "authwidget.h"

AuthWidget::AuthWidget(QWidget *parent)
    : QWidget(parent)
{
    number =  new QLineEdit;
    password  = new QLineEdit;
}

void AuthWidget::getUserInfoCallback(const UserInfo &user)
{

}

void AuthWidget::registrationCallback(const int &id)
{

}

void AuthWidget::registration()
{

}

void AuthWidget::login(QString number, QString password)
{

}

void AuthWidget::saveInChache(const bool &state)
{

}

int AuthWidget::getId() const
{
  return id;
}


