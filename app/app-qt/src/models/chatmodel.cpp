#include "chatmodel.h"
#include <memory>
#include <QDebug>
#include <unordered_set>
#include <netlib/AppNetwork.h>
#include "app-qt/src/models/usermodel.h"

ChatModel::ChatModel(QObject *parent)
    :QAbstractListModel(parent)
{
}

int ChatModel::rowCount(const QModelIndex &parent) const
{
     return items.size();
}


QVariant ChatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
           return QVariant();

    if (index.row() >= items.size())
        return QVariant();

    if (role == Qt::DisplayRole){
        Msg item = items.at(index.row());
        return QVariant::fromValue(item);
    }
    else
        return QVariant();
}

void ChatModel::createMessage(const Msg &_message)
{
     int row = this->rowCount();
    beginInsertRows(QModelIndex(),row,row + items.size() - 1);
    if(_message.text != "")
    {
        items.push_back(_message);
        int row = this->rowCount();
    }
    endInsertRows();
    emit this->dataChanged(QModelIndex(),QModelIndex());
    emit updateItems();
}

void ChatModel::newMessages(std::vector<MessageItem> msgs)
{
    int row = this->rowCount();
    auto iniqIds = getUniqueIds(msgs);
    beginInsertRows(QModelIndex(),row,row + msgs.size() - 1);
    for(auto &obj : msgs){
        qDebug() << QString::fromStdString(obj.text);
        items.emplace_back(Msg(obj));
    }
    for(auto &obj : iniqIds){
        AppNet::shared()->getUser(UserModel::instance()->getId(),obj,userInfForMessage);
    }
    endInsertRows();
}


void ChatModel::addCallbacks()
{
    auto self = shared_from_this();
    chatCallback = [self](std::vector<MessageItem>& msgs,std::optional<std::string>& err){
        if(err == std::nullopt){
            self->setData(msgs);
        }
        else{
            self->errString = err;
        }
    };
    sendMsgCallback = [self](std::optional<std::string>& err){

        if(err != std::nullopt){
            self->errString = err;
        }
    };
    changeMsgCallback = [self](std::optional<std::string>& err){
        if(err != std::nullopt){
            self->errString = err;
        }
    };
    delMsgCallback = [self](std::optional<std::string>& err){
        if(err != std::nullopt){
            self->errString = err;
        }
    };
    userInfForMessage = [self](inf::UserInfo &info,std::optional<std::string>&err){
        if(err == std::nullopt){
            std::for_each(self->items.begin(),self->items.end(),[info](Msg& msg){
                 if(msg.idOwner == info.id){
                     msg.nickname = QString::fromStdString(info.login);
                     msg.avatar = QString::fromStdString(info.avatar);
                 }
            });

            emit self->updateItems();
        }
    };
}

void ChatModel::setData(std::vector<MessageItem> &msgs)
{
    items.clear();
    int row = this->rowCount();
    items.reserve(msgs.size());
    auto iniqIds = getUniqueIds(msgs);
    beginInsertRows(QModelIndex(),row,msgs.size() - 1);
    for(auto &obj : msgs){
        qDebug() << QString::fromStdString(obj.text);
        items.emplace_back(Msg(obj));
    }
    for(auto &obj : iniqIds){
        AppNet::shared()->getUser(UserModel::instance()->getId(),obj,userInfForMessage);
    }
    endInsertRows();
}

std::function<void(std::vector<MessageItem>&,std::optional<std::string>&)>& ChatModel::getChatCallback()
{
    return chatCallback;
}

std::function<void (std::optional<std::string> &)>& ChatModel::getSendMsgCallback()
{
    return sendMsgCallback;
}

std::function<void (std::optional<std::string> &)>& ChatModel::getChangeMsgCallback()
{
    return changeMsgCallback;
}

std::function<void (std::optional<std::string> &)>& ChatModel::getDelMsgCallback()
{
    return delMsgCallback;
}

std::vector<Msg> ChatModel::getItems()
{
    return items;
}

void ChatModel::DeleteMessage(int pos)
{
    if(pos >= 0 && pos < items.size())
        items.erase(items.begin() + pos);
}

void ChatModel::getMessagesInChat(Msg lastMsg)
{
    if(lastMsg.text == ""){
        AppNet::shared()->getMsgs(UserModel::instance()->getId(),lastMsg.chatId,1,1,chatCallback);
        return;
    }
    int count = lastMsg.number / 20;
    int lastMsgs = lastMsg.number % 20;
    int curr = 0;
    for(size_t i = 0; i < count; ++i){
        AppNet::shared()->getMsgs(UserModel::instance()->getId(),lastMsg.chatId,curr+1,curr + 20,chatCallback);
        curr += 20;
    }
    if(count == 0)
        AppNet::shared()->getMsgs(UserModel::instance()->getId(),lastMsg.chatId,1,lastMsgs,chatCallback);
    else
        AppNet::shared()->getMsgs(UserModel::instance()->getId(),lastMsg.chatId,curr+1,curr + lastMsgs,chatCallback);
}

void ChatModel::Clear()
{
    beginResetModel();
    items.clear();
    endResetModel();
}


std::vector<int> ChatModel::getUniqueIds(const std::vector<MessageItem> &vec)
{
    std::unordered_set<int> set;
    std::for_each(vec.begin(),vec.end(),[&set](const MessageItem& p){
        set.insert(p.idOwner);
    });
    return std::vector<int>(set.begin(),set.end());
}


