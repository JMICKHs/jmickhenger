#include "usermodel.h"
#include <memory>
#include <QDebug>
UserModel::UserModel()
{
}

void UserModel::setData(Account &acc)
{
    myAcc = std::move(acc);
}

std::function<void (bool, std::optional<string> &)> &UserModel::getSaveAvatarCallback()
{
    return saveAvatarCallback;
}

std::function<void (bool, std::optional<string> &)> &UserModel::getChangeMeCallback()
{
    return changeMeCallback;
}

std::function<void (Account&,std::optional<string>&)>& UserModel::getAuthCallback()
{
    return authCallback;
}

std::function<void (int, std::optional<string> &)> &UserModel::getRegistrationCallback()
{
    return registrationCallback;
}

void UserModel::setCallBacks()
{
    errString = nullopt;
    saveAvatarCallback = [self = instance()](bool state,std::optional<string>& err){
        if(err == nullopt){
            self->errString = err;
        }
    };
    changeMeCallback = [self = instance()](bool state,std::optional<string>& err){
        if(err == nullopt){
            self->errString = err;
        }
    };
    registrationCallback = [self = instance()](int id,std::optional<string>& err){
        if(err == nullopt){
            self->myAcc.id = id;
            emit self->showMainWidget();
        }
        else
            self->errString = err;
    };
    authCallback = [self = instance()](Account& newAcc,std::optional<string>& err){
        if(err == nullopt){
            self->setData(newAcc);
            emit self->showMainWidget();
        }
        else
            self->errString = err;
    };
}

Account UserModel::getAcc() const
{
    return myAcc;
}

int UserModel::getId() const
{
    return myAcc.id;
}

void UserModel::setLogin(const std::string &login)
{
    myAcc.login = login;
    emit nickNameChanged(QString::fromStdString(login));
}

void UserModel::setPassword(const std::string &password)
{
    myAcc.password = password;
}
