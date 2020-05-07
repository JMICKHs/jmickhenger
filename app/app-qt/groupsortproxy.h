#ifndef GROUPSORTPROXY_H
#define GROUPSORTPROXY_H

#include <QAbstractProxyModel>
class GroupSortProxy : public QAbstractProxyModel
{
public:
    GroupSortProxy();
    int rowCount(const QModelIndex &parent) const
    {

    }
};

#endif // GROUPSORTPROXY_H
