#ifndef USETMODEL_H
#define USETMODEL_H

#include <netlib/info/Info.h>
#include <functional>
#include <QObject>

using Account = inf::MyAccount;

class UserModel : public QObject ,public enable_shared_from_this<UserModel>
{
    Q_OBJECT
public:
    UserModel();
    void setData(Account &acc);
    std::function<void(bool,std::optional<string>&)> &getSaveAvatarCallback()  ;
    std::function<void(bool,std::optional<string>&)> &getChangeMeCallback()  ;
    std::function<void(Account&,std::optional<string>&)> &getAuthCallback() ;
    std::function<void(int,std::optional<string>&)> &getRegistrationCallback();
    void setCallBacks();
    Account getAcc() const;
    int getId() const;
    void setId(int id);
    void setLogin(const std::string &login);
    void setPassword(const std::string &password);

private:
    std::optional<string> errString;
    Account myAcc;
    std::function<void(bool,std::optional<string>&)> saveAvatarCallback;
    std::function<void(bool,std::optional<string>&)> changeMeCallback;
    std::function<void(Account&,std::optional<string>&)> authCallback;
    std::function<void(int,std::optional<string>&)> registrationCallback;

signals:
    void showMainWidget();
    void nickNameChanged(const QString&);
};

#endif // USETMODEL_H
