#include "chatmodel.h"
#include <memory>
#include <QDebug>

ChatModel::ChatModel(QObject *parent)
    :QAbstractListModel(parent)
{
    chatCallback = [this](std::vector<Message>& msgs,std::optional<string>& err){
        if(err == nullopt){
            this->setData(msgs);
        }
        else{
            errString = err;
        }
    };
    sendMsgCallback = [this](bool state,std::optional<string>& err){
        if(err == nullopt){
            errString = err;
        }
    };
    changeMsgCallback = [this](bool state,std::optional<string>& err){
        if(err == nullopt){
            errString = err;
        }
    };
    delMsgCallback = [this](bool state,std::optional<string>& err){
        if(err == nullopt){
            errString = err;
        }
    };
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
        items.push_back(std::move(_message));
        int row = this->rowCount();
        this->insertRows(row,1);
    }
    emit this->dataChanged(QModelIndex(),QModelIndex());
}

void ChatModel::setData(std::vector<Message> &msgs)
{
    items = std::move(msgs);
}

std::function<void(std::vector<Message>&,std::optional<string>&)> ChatModel::getChatCallback() const
{
    return chatCallback;
}

std::function<void (bool, std::optional<string> &)> ChatModel::getSendMsgCallback() const
{
    return sendMsgCallback;
}

std::function<void (bool, std::optional<string> &)> ChatModel::getChangeMsgCallback() const
{
    return changeMsgCallback;
}

std::function<void (bool, std::optional<string> &)> ChatModel::getDelMsgCallback() const
{
    return delMsgCallback;
}
