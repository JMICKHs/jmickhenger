#include "proxymodel.h"
#include "app-qt/src/models/groupmodel.h"
#include <QDebug>

ProxyModel::ProxyModel(QObject *parent)
    :QSortFilterProxyModel(parent),searchString("")
{

}

bool ProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index0 = sourceModel()->index(source_row,0,source_parent);
    auto value = sourceModel()->data(index0).value<Chat>();
    if(QString::fromStdString(value.name).contains(searchString)){
        return  true;
    }
    else {
        return false;
    }
}

bool ProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
   return source_left.data().value<Chat>().lastMessage.time < source_right.data().value<Chat>().lastMessage.time;
}

void ProxyModel::search_String_Changed(const QString &str)
{
    searchString = str;
    invalidateFilter();
}
