#include "groupmodel.h"
#include "netlib/AppNetwork.h"


GroupModel::GroupModel(QObject *parent)
    :QAbstractListModel(parent)
{
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
    int row = this->rowCount();
    items.reserve(chats.size());
    beginInsertRows(QModelIndex(),row,chats.size() - 1);
    for(auto &obj : chats){
        items.emplace_back(Chat(obj));
    }
    auto net = AppNet::shared();
    for(auto &obj : items){
        net->getLastMsg(obj.idChat,this->lastMsgCallback);
        obj.lastMessage = Msg(lastMsg);
    }
    endInsertRows();
}

void GroupModel::addCallbacks()
{
    chatCallback = [self = shared_from_this()](vector<ChatItem> &chats, std::optional<string> &err){
        if(err == nullopt)
            self->setData(chats);
        else{
            self->errString = err;
        }
    };
    lastMsgCallback = [self = shared_from_this()](MessageItem & msg, std::optional<string> & err){
        if(err == nullopt)
            self->lastMsg = msg;
        else
            self->errString = err;
    };
    createChatCallback = [self = shared_from_this()](int,std::optional<string> &err){
        if(err != nullopt)
              self->errString = err;
    };

    delChatCallback = [self = shared_from_this()](bool state, std::optional<string> &err){
        if(err != nullopt)
              self->errString = err;
    };
    std::function<void(Change&)> chatChangeCallback;
}

std::function<void (vector<ChatItem> &, std::optional<string> &)> &GroupModel::getChatCallBack()
{
    return chatCallback;
}

std::function<void (MessageItem &, std::optional<string> &)>& GroupModel::getLastMsgCallback()
{
    return lastMsgCallback;
}

std::function<void (int, std::optional<string> &)>& GroupModel::getCreateChatCallback()
{
    return createChatCallback;
}

std::function<void (bool, std::optional<string> &)>& GroupModel::getDelChatCallback()
{
    return delChatCallback;
}

std::function<void (Change &)> &GroupModel::getChatChangeCallback()
{
    return chatChangeCallback;
}
