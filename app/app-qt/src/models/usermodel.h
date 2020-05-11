#ifndef USETMODEL_H
#define USETMODEL_H

#include <netlib/info/Info.h>
#include <functional>
#include <QObject>

using Account = inf::MyAccount;

class UserModel : public QObject
{
    Q_OBJECT
public:
    UserModel();
    void setData(Account &acc);
    std::function<void(bool,std::optional<string>&)> getSaveAvatarCallback()  ;
    std::function<void(bool,std::optional<string>&)> getChangeMeCallback()  ;
    std::function<void(Account&,std::optional<string>&)> getAuthCallback() ;
    std::function<void(int,std::optional<string>&)> getRegistrationCallback();
private:
    std::optional<string> errString;
    Account myAcc;
    std::function<void(bool,std::optional<string>&)> saveAvatarCallback;
    std::function<void(bool,std::optional<string>&)> changeMeCallback;
    std::function<void(Account&,std::optional<string>&)> authCallback;
    std::function<void(int,std::optional<string>&)> registrationCallback;
signals:
    void showMainWidget();
};

#endif // USETMODEL_H
