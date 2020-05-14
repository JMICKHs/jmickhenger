#ifndef FRIENDSMODEL_H
#define FRIENDSMODEL_H

#include <QAbstractListModel>
#include <functional>
#include <memory>

#include <netlib/info/Info.h>

using UserInf = inf::UserInfo;

Q_DECLARE_METATYPE(UserInf)

class FriendsModel : public QAbstractListModel, public enable_shared_from_this<FriendsModel>
{
public:
    FriendsModel();
    void setData(std::vector<int> &);
    void addFriend(UserInf &usr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addCallbacks();
    std::function<void(std::optional<std::string> &)>& getAddFriendCallback();
    std::function<void(std::vector<int> &,std::optional<std::string> &)>& getFrinedsCallback();
public slots:
    void getFriendsSlot();
private:
    std::function<void(std::optional<std::string> &)> addFriendCallback;
    std::function<void(std::vector<int> &,std::optional<std::string> &)> friendsCallback;
    std::vector<UserInf> items;
    std::vector<int> ids;
    std::optional<std::string> errString;
};

#endif // FRIENDSMODEL_H
