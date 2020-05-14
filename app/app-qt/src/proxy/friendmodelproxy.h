#ifndef FRIENDMODELPROXY_H
#define FRIENDMODELPROXY_H

#include <QSortFilterProxyModel>

class FriendModelProxy : public QSortFilterProxyModel
{
public:
    FriendModelProxy(QObject *parent = nullptr);

public slots:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
    void search_String_Changed(const QString &);
private:
    QString searchString;
};

#endif // FRIENDMODELPROXY_H
