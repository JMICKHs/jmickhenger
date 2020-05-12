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
        Msg item = items.at(index.row());
        return QVariant::fromValue(item);
    }
    else
        return QVariant();
}

void ChatModel::createMessage(Msg &_message)
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
    chatCallback = [self = shared_from_this()](std::vector<MessageItem>& msgs,std::optional<string>& err){
        if(err == nullopt){
            self->setData(msgs);
        }
        else{
            self->errString = err;
        }
    };
    sendMsgCallback = [self = shared_from_this()](std::optional<string>& err){
        if(err != nullopt){
            self->errString = err;
        }
    };
    changeMsgCallback = [self = shared_from_this()](std::optional<string>& err){
        if(err != nullopt){
            self->errString = err;
        }
    };
    delMsgCallback = [self = shared_from_this()](std::optional<string>& err){
        if(err != nullopt){
            self->errString = err;
        }
    };
}

void ChatModel::setData(std::vector<MessageItem> &msgs)
{
    items.clear();
    int row = this->rowCount();
    items.reserve(msgs.size());
    beginInsertRows(QModelIndex(),row,msgs.size() - 1);
    for(auto &obj : msgs){
        qDebug() << QString::fromStdString(obj.text);
        items.emplace_back(Msg(obj));

    }

    endInsertRows();
}

std::function<void(std::vector<MessageItem>&,std::optional<string>&)>& ChatModel::getChatCallback()
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

void ChatModel::DeleteMessage(int pos)
{
    qDebug() <<pos;
    if(pos >= 0 && pos < items.size())
        items.erase(items.begin() + pos);
}


