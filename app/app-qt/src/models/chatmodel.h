#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QAbstractListModel>
#include "app-qt/src/custommbutton/custombutton.h"
#include "app-qt/src/chatlist/chatlist.h"

class ChatModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ChatModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void createMessage(const Message &_message);
private:
    std::vector<Message> items;
    bool newMessageOnBottom;

signals:
};

#endif // CHATMODEL_H
