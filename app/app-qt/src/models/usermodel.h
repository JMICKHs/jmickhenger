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
    void setData(Account &acc);
    std::function<void(bool,std::optional<std::string>&)> &getSaveAvatarCallback()  ;
    std::function<void(bool,std::optional<std::string>&)> &getChangeMeCallback()  ;
    std::function<void(Account&,std::optional<std::string>&)> &getAuthCallback() ;
    std::function<void(int,std::optional<std::string>&)> &getRegistrationCallback();
    void setCallBacks();
    void setAvatar(const QString &avatar);
    Account getAcc() const;
    int getId() const;
    void setId(int id);
    void setLogin(const std::string &login);
    void setPassword(const std::string &password);
    static UserModel* instance(){
        static UserModel inst;
        return &inst;
    }

private:
    UserModel();
    std::optional<std::string> errString;
    Account myAcc;
    std::function<void(bool,std::optional<std::string>&)> saveAvatarCallback;
    std::function<void(bool,std::optional<std::string>&)> changeMeCallback;
    std::function<void(Account&,std::optional<std::string>&)> authCallback;
    std::function<void(int,std::optional<std::string>&)> registrationCallback;

signals:
    void showMainWidget();
    void nickNameChanged(const QString&);
    void stopAnimationSignal();
};

#endif // USETMODEL_H
