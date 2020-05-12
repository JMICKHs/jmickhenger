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
    saveAvatarCallback = [self = shared_from_this()](bool state,std::optional<string>& err){
        if(err == nullopt){
            self->errString = err;
        }
    };
    changeMeCallback = [self = shared_from_this()](bool state,std::optional<string>& err){
        if(err == nullopt){
            self->errString = err;
        }
    };
    registrationCallback = [self = shared_from_this()](int id,std::optional<string>& err){
        if(err == nullopt){
            emit self->showMainWidget();
        }
        else
            self->errString = err;
    };
    authCallback = [self = shared_from_this()](Account& newAcc,std::optional<string>& err){
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
