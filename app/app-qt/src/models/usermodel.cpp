#include "usermodel.h"

UserModel::UserModel()
{
    saveAvatarCallback = [this](bool state,std::optional<string>& err){
        if(err == nullopt){
            errString = err;
        }
    };
    changeMeCallback = [this](bool state,std::optional<string>& err){
        if(err == nullopt){
            errString = err;
        }
    };
    registrationCallback = [this](int id,std::optional<string>& err){
        if(err == nullopt){
            errString = err;
        }
        else
            emit showMainWidget();
    };
    authCallback = [this](Account& newAcc,std::optional<string>& err){
        if(err != nullopt){
            this->setData(newAcc);
            emit showMainWidget();
        }
        else
            errString = err;
    };
}

void UserModel::setData(Account &acc)
{
    myAcc = std::move(acc);
}

std::function<void (bool, std::optional<string> &)> UserModel::getSaveAvatarCallback()
{
    return saveAvatarCallback;
}

std::function<void (bool, std::optional<string> &)> UserModel::getChangeMeCallback()
{
    return changeMeCallback;
}

std::function<void (Account&,std::optional<string>&)> UserModel::getAuthCallback()
{
    return authCallback;
}

std::function<void (int, std::optional<string> &)> UserModel::getRegistrationCallback()
{
    return registrationCallback;
}
