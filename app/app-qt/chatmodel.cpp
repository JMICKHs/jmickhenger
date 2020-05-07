#include "chatmodel.h"
#include <QDebug>

ChatModel::ChatModel(QObject *parent)
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

void ChatModel::createMessage(const Message &_message)
{
    if(_message.text != "")
    {
        items.push_back(std::move(_message));
        int row = this->rowCount();
        this->insertRows(row,1);
    }
    emit this->dataChanged(QModelIndex(),QModelIndex());
}
