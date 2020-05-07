#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include <QAbstractListModel>
#include <custommbutton/custombutton.h>
#include <../netlib/info/Info.h>

using Chat = inf::ChatRoom;

Q_DECLARE_METATYPE(Chat)

class GroupModel : public QAbstractListModel
{
    Q_OBJECT
public:
    GroupModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addItem(const Chat &item);
private:
    std::vector<Chat> items;
signals:

public slots:
};

#endif // GROUPMODEL_H
