#include "friendmodelproxy.h"
#include "app-qt/src/models/friendsmodel.h"
#include <QDebug>

FriendModelProxy::FriendModelProxy(QObject *parent)
{

}

bool FriendModelProxy::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index0 = sourceModel()->index(source_row,0,source_parent);
    if(index0.data() == Qt::DisplayRole)
        return true;
    auto value = sourceModel()->data(index0).value<UserInf>();
    if(QString::fromStdString(value.login).contains(searchString)){
        return  true;
    }
    else {
        return false;
    }
}

bool FriendModelProxy::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{

}

void FriendModelProxy::search_String_Changed(const QString &str)
{
    qDebug() <<str;
    searchString = str;
    invalidateFilter();
}
