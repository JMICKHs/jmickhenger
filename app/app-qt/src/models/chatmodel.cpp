#include "chatmodel.h"
#include <memory>
#include <QDebug>
#include <unordered_set>
#include <netlib/AppNetwork.h>
#include "app-qt/src/models/usermodel.h"
#include <QPixmap>

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

void ChatModel::createMessage(Msg &_message,std::optional<QPixmap> &img)
{
    QByteArray array;

     int row = this->rowCount();
    beginInsertRows(QModelIndex(),row,row + 1);
    if(_message.text != "")
    {
        if(img)
            _message.img = std::make_shared<QPixmap>(img.value());
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
    beginInsertRows(QModelIndex(),row,row + msgs.size());
    int myId = UserModel::instance()->getId();
    for(auto &obj : msgs){
        qDebug() << QString::fromStdString(obj.text);
        items.emplace_back(Msg(obj));
        if(obj.checked && obj.idOwner == myId){
            items[items.size() - 1].type = MessageType::SELF_MESSAGE_DONE;
        }
        else{
            items[items.size() - 1].type = MessageType::SELF_MESSAGE_IN_PROGRESS;
        }
        if(obj.image != ""){
            QString pix = QString::fromStdString(obj.image);
            QByteArray buf2 = QByteArray::fromBase64(pix.toLocal8Bit());
            QPixmap mp;
            mp.loadFromData(buf2);
            items[items.size() - 1].img = std::make_shared<QPixmap>(mp);
        }
    }
    for(auto &obj : iniqIds){
        AppNet::shared()->getUser(myId,obj,userInfForMessage);
    }
    endInsertRows();
    emit this->dataChanged(QModelIndex(),QModelIndex());
    emit updateItems();
}

void ChatModel::msgsChecked()
{
    qDebug() <<"checked";
    int id = UserModel::instance()->getId();
    std::for_each(items.begin(),items.end(),[id](Msg &msg){
            if(msg.idOwner == id){
                msg.type = MessageType::SELF_MESSAGE_DONE;
            }
    });
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
    sendMsgCallback = [self](int number,std::optional<std::string>& err){
        if(err == std::nullopt){
            auto it = std::find_if(self->items.begin(),self->items.end(),[number](const Msg &msg){
                return msg.number == number;
            });
            if(it != self->items.end()){
                it.base()->type = MessageType::SELF_MESSAGE_DONE;
            }
        }
        else{
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
    lastMsgAndGet = [self](MessageItem & msg, std::optional<std::string> &err){
        if(err == std::nullopt){
            if(msg.text == ""){
                AppNet::shared()->getMsgs(UserModel::instance()->getId(),msg.chatId,1,1,self->chatCallback);
                return;
            }
            int count = msg.number / 15;
            int lastMsgs = msg.number % 15;
            int curr = 0;
            for(size_t i = 0; i < count; ++i){
                AppNet::shared()->getMsgs(UserModel::instance()->getId(),msg.chatId,curr+1,curr + 15,self->chatCallback);
                curr += 15;
            }
            if(count == 0)
                AppNet::shared()->getMsgs(UserModel::instance()->getId(),msg.chatId,1,lastMsgs,self->chatCallback);
            else
                AppNet::shared()->getMsgs(UserModel::instance()->getId(),msg.chatId,curr+1,curr + lastMsgs,self->chatCallback);
        }
    };
}

void ChatModel::setData(std::vector<MessageItem> &msgs)
{
    items.clear();
    int row = this->rowCount();
    items.reserve(msgs.size());
    auto iniqIds = getUniqueIds(msgs);
    beginInsertRows(QModelIndex(),row,row + msgs.size());
    for(auto &obj : msgs){
        items.emplace_back(Msg(obj));
    }
    for(auto &obj : iniqIds){
        AppNet::shared()->getUser(UserModel::instance()->getId(),obj,userInfForMessage);
    }
    endInsertRows();
    emit this->dataChanged(QModelIndex(),QModelIndex());
    emit this->updateItems();
}

std::function<void(std::vector<MessageItem>&,std::optional<std::string>&)>& ChatModel::getChatCallback()
{
    return chatCallback;
}

std::function<void (int,std::optional<std::string> &)>& ChatModel::getSendMsgCallback()
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

std::function<void (MessageItem &, std::optional<std::string> &)> &ChatModel::getLastMsgAndGet()
{
    return lastMsgAndGet;
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


