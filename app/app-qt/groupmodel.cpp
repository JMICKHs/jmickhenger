#include "groupmodel.h"


GroupModel::GroupModel(QObject *parent)
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
           GroupItem item = items.at(index.row());
           return QVariant::fromValue(item);
       }
       else
           return QVariant();
}

void GroupModel::addItem(const GroupItem &item)
{
    items.push_back(item);
    int row = this->rowCount();

    this->insertRows(row,1);
}
