#ifndef FRIENDSMODEL_H
#define FRIENDSMODEL_H

#include <QAbstractListModel>
#include <functional>
#include <memory>

#include <netlib/info/Info.h>
#include "app-qt/src/models/usermodel.h"

class FriendsModel : public QAbstractListModel, public std::enable_shared_from_this<FriendsModel>
{
    Q_OBJECT
public:
    FriendsModel();
    void setData(std::vector<int> &);
    void addFriend(int nid);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addCallbacks();
    std::function<void(int,std::optional<std::string> &)>& getAddFriendCallback();
    std::function<void(std::vector<int> &,std::optional<std::string> &)>& getFrinedsCallback();
    void Clear();
public slots:
    void addFriendSlot(const QString&);
signals:
    void updateForNames();
private:
    std::function<void(int ,std::optional<std::string> &)> addFriendCallback;
    std::function<void(std::vector<int> &,std::optional<std::string> &)> friendsCallback;
    std::function<void(inf::UserInfo &user,std::optional<std::string>&)> userForFriend;
    std::vector<UserInf> items;
    std::optional<std::string> errString;
    int currId;
};

#endif // FRIENDSMODEL_H
