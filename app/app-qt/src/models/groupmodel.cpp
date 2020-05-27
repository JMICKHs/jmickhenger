#include "groupmodel.h"
#include "netlib/AppNetwork.h"
#include "app-qt/src/models/usermodel.h"
#include <QDebug>
#include <chrono>


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
    beginInsertRows(QModelIndex(),row,row + chats.size() - 1);
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
    auto self = shared_from_this();
    chatCallback = [self](std::vector<ChatItem> &chats, std::optional<std::string> &err){
        if(err == std::nullopt){
            self->setData(chats);
        }
        else{
            self->errString = err;
        }
    };
    lastMsgCallback = [self](MessageItem & msg, std::optional<std::string> & err){
        if(err == std::nullopt){
            auto it = std::find_if(self->items.begin(),self->items.end(),[msg](const Chat &chat){
                return  chat.idChat == msg.chatId;
            });
            it.base()->lastMessage = msg;
            AppNet::shared()->getUser(UserModel::instance()->getId(),msg.idOwner,self->userInfForMessage);
            emit self->updateItems();
        }
        else
            self->errString = err;
    };
    createChatCallback = [self](int id,std::optional<std::string> &err){
        if(err == std::nullopt){
            self->items[self->items.size()-1].idChat = id;
            AppNet::shared()->getLastMsg(UserModel::instance()->getId(),id,self->lastMsgCallback);
            qDebug() <<"obs set";
            AppNet::shared()->setObserverChat(id,self->chatChangeCallback);
            emit self->updateItems();
        }
        else
            self->errString = err;

    };

    delChatCallback = [self](bool state, std::optional<std::string> &err){
        if(err != std::nullopt)
              self->errString = err;
    };
    chatChangeCallback = [self](inf::ChatChange &change){
        if(change.action == "delChat"){
            auto it = std::find_if(self->items.begin(), self->items.end(),[change](const Chat &chat){
                return  chat.idChat == change.idChat;
            });
            self->items.erase(it);
        }
        if(change.action == "delChat"){
            auto it = std::find_if(self->items.begin(), self->items.end(),[change](const Chat &chat){
                return  chat.idChat == change.idChat;
            });
            self->items.erase(it);
        }
        if(change.action == "addMessage"){
            if(change.idChat == self->currChatId){
                AppNet::shared()->readChat(UserModel::instance()->getId(),change.idChat,self->readMsgCallback);
                emit self->sendNewMessages(change.messages);
            }
            auto it = std::find_if(self->items.begin(),self->items.end(),[change](Chat &chat){
                return chat.idChat == change.idChat;
            });
            it.base()->lastMessage = change.messages[change.messages.size() -1];
            AppNet::shared()->getUser(UserModel::instance()->getId(),(*it).lastMessage.idOwner,self->userInfForMessage);
            emit self->updateItems();

        }
        if(change.action == "delMessage"){
            if(change.idChat == self->currChatId){
                qDebug() <<change.messages.begin().base()->number;
               emit self->deleteMsg(change.messages.begin().base()->number);
            }
        }
        if(change.action == "changeMessage"){
            if(change.idChat == self->currChatId){
                 emit self->editMsg(change.messages[change.messages.size() -1]);
            }
        }
        if(change.action == "readMessage"){
            if(self->currChatId == change.idChat){
                emit self->messageChecked();
            }
        }
    };
    newUnknownChatCallback = [self](inf::ChatRoom &room, std::optional<std::string>&){
        Chat item;
        item.idChat = room.idChat;
        item.name = room.name;
        self->addItem(item);
        AppNet::shared()->getLastMsg(UserModel::instance()->getId(),room.idChat,self->getLastMsgCallback());
        AppNet::shared()->setObserverChat(room.idChat,self->chatChangeCallback);
    };
    unknownChatRoomAdd = [self](Change& change){
        AppNet::shared()->getChatRoom(UserModel::instance()->getId(),change.idChat,self->newUnknownChatCallback);
    };
    chatRoom = [self](inf::ChatRoom &room, std::optional<std::string>&err){
          if(err == std::nullopt){
              emit self->sendChatRoom(room);
          }
    };
    userInfForMessage = [self](inf::UserInfo &info,std::optional<std::string>&err){
        if(err == std::nullopt){
            std::for_each(self->items.begin(),self->items.end(),[info](Chat &chat){
                 if(chat.lastMessage.idOwner == info.id){
                     chat.lastMessage.nickname = QString::fromStdString(info.login);
                     chat.lastMessage.avatar = QString::fromStdString(info.avatar);
                 }
            });

            emit self->updateItems();
        }
    };
    readMsgCallback= [self](std::optional<std::string> &err){

    };
    std::function<void(Change&)> chatChangeCallback;
}

void GroupModel::chatInfoSet(int id)
{
     AppNet::shared()->getChatRoom(UserModel::instance()->getId(),id,chatRoom);
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

std::function<void (Change &)> &GroupModel::getUnknownChatRoomAdd()
{
    return unknownChatRoomAdd;
}

std::function<void (inf::ChatRoom &, std::optional<std::string> &)> &GroupModel::getChatRoom()
{
    return chatRoom;
}

std::function<void (std::optional<std::string> &)> &GroupModel::getReadMsgCallback()
{
    return readMsgCallback;
}

std::vector<Chat> GroupModel::getItems()
{
    return items;
}

Msg GroupModel::getLastMsg(int id) const
{
    auto it = std::find_if(items.begin(), items.end(),[id](const Chat &chat){
        return  chat.idChat == id;
    });
    if(it != items.end()){
        return it.base()->lastMessage;
    }
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

void GroupModel::setLastMessage(const Msg &msg)
{
    auto it = std::find_if(items.begin(),items.end(),[msg](Chat &chat){
        return msg.chatId == chat.idChat;
    });
    if(it != items.end()){
        it->lastMessage = msg;
    }
    this->updateItems();
}

