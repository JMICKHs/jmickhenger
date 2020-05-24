#include "usermodel.h"
#include <memory>
#include <QDebug>

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

std::function<void (Account &, std::optional<std::string> &)> &UserModel::getAuthWithCacheCallback()
{
    return authWithCacheCallback;
}

void UserModel::setCallBacks()
{
    auto self = instance();
    errString = std::nullopt;
    saveAvatarCallback = [self](bool state,std::optional<std::string>& err){
        if(err == std::nullopt){
            self->errString = err;
        }
    };
    changeMeCallback = [self](bool state,std::optional<std::string>& err){
        if(err == std::nullopt){
            self->errString = err;
        }
    };
    registrationCallback = [self](int id,std::optional<std::string>& err){
        if(err == std::nullopt){
            self->myAcc.id = id;
            emit self->showMainWidget();
        }
        else{
            self->errString = err;
            emit self->setRegInfo(QString::fromStdString(err.value()));
        }
        emit self->stopAnimationSignal();
        emit self->upFlag(false);

    };
    authCallback = [self](Account& newAcc,std::optional<std::string>& err){
        if(err == std::nullopt){
            self->setData(newAcc);
            emit self->showMainWidget();
        }
        else{
            self->errString = err;
            emit self->setLogInfo(QString::fromStdString(err.value()));
        }
        emit self->stopAnimationSignal();
        emit self->upFlag(false);
    };
    authWithCacheCallback = [self](Account& newAcc,std::optional<std::string>& err){
        if(err == std::nullopt){
            self->setData(newAcc);
            emit self->showMainWidget();
        }
        else
            self->errString = err;
    };
}

void UserModel::setAvatar(const QString &avatar)
{
    myAcc.avatar = avatar.toStdString();
}

void UserModel::setAcc(Account &acc)
{
    myAcc = std::move(acc);
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

