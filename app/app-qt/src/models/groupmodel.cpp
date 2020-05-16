#include "groupmodel.h"
#include "netlib/AppNetwork.h"
#include "app-qt/src/models/usermodel.h"
#include <QDebug>


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
    items.emplace_back(item);
    endInsertRows();
}

void GroupModel::setData(std::vector<ChatItem> &chats)
{
    items.clear();
    int row = this->rowCount();
    beginInsertRows(QModelIndex(),row,chats.size() - 1);
    for(auto &obj : chats){
        items.emplace_back(obj);
    }
    auto net = AppNet::shared();
    for(size_t i = 0; i < items.size(); ++i){
        net->getLastMsg(UserModel::instance()->getId(),items[i].idChat,this->lastMsgCallback);
        AppNet::shared()->setObserverChat(items[i].idChat,chatChangeCallback);
    }
    endInsertRows();
}

void GroupModel::addCallbacks()
{
    chatCallback = [self = shared_from_this()](std::vector<ChatItem> &chats, std::optional<std::string> &err){
        if(err == std::nullopt){
            self->setData(chats);
        }
        else{
            self->errString = err;
        }
    };
    lastMsgCallback = [self = shared_from_this()](MessageItem & msg, std::optional<std::string> & err){
        if(err == std::nullopt){
            auto it = std::find_if(self->items.begin(),self->items.end(),[msg](const Chat &chat){
                return  chat.idChat == msg.chatId;
            });
            it.base()->lastMessage = msg;
        }
        else
            self->errString = err;
    };
    createChatCallback = [self = shared_from_this()](int id,std::optional<std::string> &err){
        if(err == std::nullopt)
            self->items[self->items.size()].idChat = id;
        else
            self->errString = err;
    };

    delChatCallback = [self = shared_from_this()](bool state, std::optional<std::string> &err){
        if(err != std::nullopt)
              self->errString = err;
    };
    unknownChatChangeCallback = [self = shared_from_this()](inf::ChatChange &change){
        AppNet::shared()->getChatRoom(UserModel::instance()->getId(),change.idChat,self->unknownChatRoomAdd);
    };
    chatChangeCallback = [self = shared_from_this()](inf::ChatChange &change){
        if(change.action == "changeChat"){

        }
        if(change.action == "delChat"){
            auto it = std::find_if(self->items.begin(), self->items.end(),[change](const Chat &chat){
                return  chat.idChat == change.idChat;
            });
            self->items.erase(it);
        }
    };
    unknownChatRoomAdd = [self = shared_from_this()](inf::ChatRoom &room, std::optional<std::string>&err){
        if(err == std::nullopt)
            self->unknownChatCreate(room);
    };
    std::function<void(Change&)> chatChangeCallback;
}

std::function<void (std::vector<ChatItem> &, std::optional<std::string> &)> &GroupModel::getChatCallBack()
{
    return chatCallback;
}

std::function<void (MessageItem &, std::optional<std::string> &)>& GroupModel::getLastMsgCallback()
{
    return lastMsgCallback;
}

std::function<void (int, std::optional<std::string> &)>& GroupModel::getCreateChatCallback()
{
    return createChatCallback;
}

std::function<void (bool, std::optional<std::string> &)>& GroupModel::getDelChatCallback()
{
    return delChatCallback;
}

std::function<void (Change &)> &GroupModel::getChatChangeCallback()
{
    return chatChangeCallback;
}

std::function<void (Change &)> &GroupModel::getUnknownChatChangeCallback()
{
    return unknownChatChangeCallback;
}

std::function<void (inf::ChatRoom &, std::optional<std::string> &)> &GroupModel::getChatRoom()
{
    return chatRoom;
}

void GroupModel::messageCreateByUser(const Msg &msg)
{
    auto it = std::find_if(items.begin(), items.end(),[msg](const Chat &chat){
        return  chat.idChat == msg.chatId;
    });
    it.base()->lastMessage = msg;
}

void GroupModel::createChatByUser(const inf::ChatRoom &room)
{
    int row = this->rowCount();
    Chat chat;
    chat.name = room.name;
    beginInsertRows(QModelIndex(),row,row);
    items.emplace_back(chat);
    endInsertRows();
    AppNet::shared()->createChat(room,createChatCallback);
    AppNet::shared()->setObserverChat(room.idChat,chatChangeCallback);
}

void GroupModel::unknownChatCreate(inf::ChatRoom &room)
{
    int row = this->rowCount();
    Chat chat;
    chat.name = room.name;
    beginInsertRows(QModelIndex(),row,row);
    items.emplace_back(chat);
    endInsertRows();
    AppNet::shared()->getLastMsg(UserModel::instance()->getId(),room.idChat,getLastMsgCallback());
    AppNet::shared()->setObserverChat(room.idChat,chatChangeCallback);
}
