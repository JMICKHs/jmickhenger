#include "friendsmodel.h"

FriendsModel::FriendsModel()
{

}

int FriendsModel::rowCount(const QModelIndex &parent) const
{
    return items.size();
}

QVariant FriendsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
           return QVariant();

    if (index.row() >= items.size())
        return QVariant();

    if (role == Qt::DisplayRole){
        UserInf item = items.at(index.row());
        return QVariant::fromValue(item);
    }
    else
        return QVariant();
}

void FriendsModel::addCallbacks()
{

}
std::function<void(std::optional<std::string> &)>& FriendsModel::getAddFriendCallback()
{
    return addFriendCallback;
}

std::function<void (std::vector<int> &, std::optional<string> &)> &FriendsModel::getFrinedsCallback()
{
    return friendsCallback;
}
