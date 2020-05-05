#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QAbstractListModel>
#include <custommbutton/CustomButton.h>
#include "chatlist/chatlist.h"

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

signals:

public slots:
    void messageCreated(const Message &_message);
};

#endif // CHATMODEL_H
