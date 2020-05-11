#include "groupmodel.h"


GroupModel::GroupModel(QObject *parent)
    :QAbstractListModel(parent)
{
    chatCallback = [this](vector<ChatItem> &chats, std::optional<string> &err){
        if(err == nullopt)
            this->setData(chats);
        else{
            errString = err;
        }
    };
    std::function<void(Msg &, std::optional<string> &)>  lastMsgCallback;
    createChatCallback = [this](int,std::optional<string> &err){
        if(err != nullopt)
              errString = err;
    };

    delChatCallback = [this](bool state, std::optional<string> &err){
        if(err != nullopt)
              errString = err;
    };
    std::function<void(Change&)> chatChangeCallback;
}

int GroupModel::rowCount(const QModelIndex &parent) const
{
    return items.size();
}

QVariant GroupModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
           return QVariant();

       if (index.row() >= items.size())
           return QVariant();

       if (role == Qt::DisplayRole){
           Chat item = items.at(index.row());
           return QVariant::fromValue(item);
       }
       else
           return QVariant();
}

void GroupModel::addItem(Chat &item)
{
    int row = this->rowCount();
    beginInsertRows(QModelIndex(),row,row);
    items.push_back(item);
    endInsertRows();
}

void GroupModel::setData(std::vector<ChatItem> &chats)
{
    items.clear();
    for(auto &obj : chats){
        items.emplace_back(Chat(obj));
    }
}

std::function<void (vector<ChatItem> &, std::optional<string> &)> GroupModel::getChatCallBack()
{
    return chatCallback;
}

std::function<void (Msg &, std::optional<string> &)> GroupModel::getLastMsgCallback()
{
    return lastMsgCallback;
}

std::function<void (int, std::optional<string> &)> GroupModel::getCreateChatCallback()
{
    return createChatCallback;
}

std::function<void (bool, std::optional<string> &)> GroupModel::getDelChatCallback()
{
    return delChatCallback;
}

std::function<void (Change &)> GroupModel::getChatChangeCallback()
{
    return chatChangeCallback;
}
