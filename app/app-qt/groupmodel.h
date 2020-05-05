#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include <QAbstractListModel>
#include <custommbutton/CustomButton.h>

struct GroupItem{
    int id;
    std::vector<int> userIds;
    QString name;
    QString lastMessage;
    QString time;

};
Q_DECLARE_METATYPE(GroupItem)

class GroupModel : public QAbstractListModel
{
    Q_OBJECT
public:
    GroupModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addItem(const GroupItem &item);
private:
    std::vector<GroupItem> items;
signals:

public slots:
};

#endif // GROUPMODEL_H
