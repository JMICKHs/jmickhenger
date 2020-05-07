#ifndef PROXYMODEL_H
#define PROXYMODEL_H


#include <QSortFilterProxyModel>
#include <QAbstractProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    ProxyModel(QObject *parent = nullptr);
public slots:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
    void search_String_Changed(const QString &);
private:
    QString searchString;
};

#endif // PROXYMODEL_H
