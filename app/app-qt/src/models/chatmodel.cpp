#include "chatmodel.h"
#include <memory>
#include <QDebug>

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
        Message item = items.at(index.row());
        return QVariant::fromValue(item);
    }
    else
        return QVariant();
}

void ChatModel::createMessage(Message &_message)
{
    if(_message.text != "")
    {
        items.push_back(_message);
        int row = this->rowCount();
        this->insertRows(row,1);
    }
    emit this->dataChanged(QModelIndex(),QModelIndex());
}

void ChatModel::addCallbacks()
{
    chatCallback = [self = shared_from_this()](std::vector<Message>& msgs,std::optional<string>& err){
        if(err == nullopt){
            self->setData(msgs);
        }
        else{
            self->errString = err;
        }
    };
    sendMsgCallback = [self = shared_from_this()](std::optional<string>& err){
        if(err == nullopt){
            self->errString = err;
        }
    };
    changeMsgCallback = [self = shared_from_this()](std::optional<string>& err){
        if(err == nullopt){
            self->errString = err;
        }
    };
    delMsgCallback = [self = shared_from_this()](std::optional<string>& err){
        if(err == nullopt){
            self->errString = err;
        }
    };
}

void ChatModel::setData(std::vector<Message> &msgs)
{
    items = std::move(msgs);
}

std::function<void(std::vector<Message>&,std::optional<string>&)>& ChatModel::getChatCallback()
{
    return chatCallback;
}

std::function<void (std::optional<string> &)>& ChatModel::getSendMsgCallback()
{
    return sendMsgCallback;
}

std::function<void (std::optional<string> &)>& ChatModel::getChangeMsgCallback()
{
    return changeMsgCallback;
}

std::function<void (std::optional<string> &)>& ChatModel::getDelMsgCallback()
{
    return delMsgCallback;
}
