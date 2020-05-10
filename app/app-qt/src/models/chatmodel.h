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
    void createMessage(Message &_message);
    void setData(std::vector<Message>& msgs);
    std::function<void(std::vector<Message>&,std::optional<string>&)> getChatCallback() ;
    std::function<void(bool,std::optional<string>&)> getSendMsgCallback() ;
    std::function<void(bool,std::optional<string>&)> getChangeMsgCallback() ;
    std::function<void(bool,std::optional<string>&)> getDelMsgCallback() ;
private:
    std::vector<Message> items;
    bool newMessageOnBottom;
    std::optional<string> errString;
    std::function<void(std::vector<Message>&,std::optional<string>&)> chatCallback;
    std::function<void(bool,std::optional<string>&)> sendMsgCallback;
    std::function<void(bool,std::optional<string>&)> changeMsgCallback;
    std::function<void(bool,std::optional<string>&)> delMsgCallback;
signals:
};

#endif // CHATMODEL_H
