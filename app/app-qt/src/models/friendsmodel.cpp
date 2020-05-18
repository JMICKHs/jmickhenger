#include "friendsmodel.h"
#include "netlib/AppNetwork.h"
#include "app-qt/src/models/usermodel.h"

FriendsModel::FriendsModel()
{

}

void FriendsModel::setData(std::vector<int> &_ids)
{
    items.clear();
    beginInsertRows(QModelIndex(),0,_ids.size() - 1);
    for(size_t i = 0; i < _ids.size(); ++i){
        UserInf inf;
        inf.id = _ids[i];
        items.push_back(inf);
    }
    for(size_t i = 0 ; i < _ids.size(); ++i){
       AppNet::shared()->getUser(UserModel::instance()->getId(),_ids[i],userForFriend);
    }
    endInsertRows();
}

void FriendsModel::addFriend(int login)
{
    int row = this->rowCount();
    beginInsertRows(QModelIndex(),row,row);
    UserInf user;
    user.id = login;
    items.push_back(std::move(user));
    endInsertRows();
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
    addFriendCallback = [self = shared_from_this()](std::optional<std::string> &err){
        if(err == std::nullopt){
            self->addFriend(self->currId);
            AppNet::shared()->getUser(UserModel::instance()->getId(),self->currId,self->userForFriend);
        }
        else
            self->errString = err;
    };
    friendsCallback = [self = shared_from_this()](std::vector<int> &ids,std::optional<std::string> &err){
        if(err == std::nullopt){
            self->setData(ids);
        }
        else{
            self->errString = err;
        }
    };
    userForFriend = [self = shared_from_this()](inf::UserInfo &user,std::optional<std::string>& err){
        if(err == std::nullopt){
            auto it = std::find_if(self->items.begin(),self->items.end(),[user](const UserInf &inf){
                return inf.id == user.id;
            });
            if(it != self->items.end()){
                it.base()->login = user.login;
                it.base()->pathToAvatar = user.pathToAvatar;
            }
        }
        else{
            self->errString = err;
        }
        self->emit updateForNames();
    };
}
std::function<void(std::optional<std::string> &)>& FriendsModel::getAddFriendCallback()
{
    return addFriendCallback;
}

std::function<void (std::vector<int> &, std::optional<std::string> &)> &FriendsModel::getFrinedsCallback()
{
    return friendsCallback;
}

void FriendsModel::Clear()
{
    items.clear();
}

void FriendsModel::addFriendSlot(int id)
{
    currId = id;
    AppNet::shared()->addFrnd(UserModel::instance()->getId(),currId,addFriendCallback);
}