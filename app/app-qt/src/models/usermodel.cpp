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

std::function<void (bool, std::optional<std::string> &)> &UserModel::getSaveAvatarCallback()
{
    return saveAvatarCallback;
}

std::function<void (bool, std::optional<std::string> &)> &UserModel::getChangeMeCallback()
{
    return changeMeCallback;
}

std::function<void (Account&,std::optional<std::string>&)>& UserModel::getAuthCallback()
{
    return authCallback;
}

std::function<void (int, std::optional<std::string> &)> &UserModel::getRegistrationCallback()
{
    return registrationCallback;
}

void UserModel::setCallBacks()
{
    errString = std::nullopt;
    saveAvatarCallback = [self = instance()](bool state,std::optional<std::string>& err){
        if(err == std::nullopt){
            self->errString = err;
        }
    };
    changeMeCallback = [self = instance()](bool state,std::optional<std::string>& err){
        if(err == std::nullopt){
            self->errString = err;
        }
    };
    registrationCallback = [self = instance()](int id,std::optional<std::string>& err){
        if(err == std::nullopt){
            self->myAcc.id = id;
            emit self->showMainWidget();
        }
        else
            self->errString = err;
        emit self->stopAnimationSignal();

    };
    authCallback = [self = instance()](Account& newAcc,std::optional<std::string>& err){
        if(err == std::nullopt){
            self->setData(newAcc);
            emit self->showMainWidget();
        }
        else
            self->errString = err;
        emit self->stopAnimationSignal();
    };
}

void UserModel::setAvatar(const QString &avatar)
{
    myAcc.pathToAvatar = avatar.toStdString();
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
