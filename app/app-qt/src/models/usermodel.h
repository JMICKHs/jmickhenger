#ifndef USETMODEL_H
#define USETMODEL_H

#include <netlib/info/Info.h>
#include <functional>

using Account = inf::MyAccount;

class UserModel
{
public:
    UserModel();
    void setData(Account &acc);
    std::function<void(bool,std::optional<string>&)> getSaveAvatarCallback()  ;
    std::function<void(bool,std::optional<string>&)> getChangeMeCallback()  ;
    std::function<void(Account&,std::optional<string>&)> getAuthCallback() ;
    std::function<void(bool,std::optional<string>&)> getRegistrationCallback();
private:
    std::optional<string> errString;
    Account myAcc;
    std::function<void(bool,std::optional<string>&)> saveAvatarCallback;
    std::function<void(bool,std::optional<string>&)> changeMeCallback;
    std::function<void(Account&,std::optional<string>&)> authCallback;
    std::function<void(bool,std::optional<string>&)> registrationCallback;

};

#endif // USETMODEL_H
