#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include <QAbstractListModel>
#include "app-qt/src/custommbutton/custombutton.h"
#include <netlib/info/Info.h>
#include "app-qt/src/models/chatmodel.h"
#include <functional>
#include <memory>

using ChatItem = inf::ChatInfo;
using Change = inf::ChatChange;

class Chat : public ChatItem{
public:
    Msg lastMessage;
    Chat(ChatItem &item)
        :ChatItem(std::move(item)){
    }
    Chat(){};
};

Q_DECLARE_METATYPE(Chat)

class GroupModel : public QAbstractListModel,public enable_shared_from_this<GroupModel>
{
    Q_OBJECT
public:
    GroupModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addItem(Chat &item);
    void setData(std::vector<ChatItem> &);
    void addCallbacks();

    std::function<void(vector<ChatItem> &, std::optional<string> &)> &getChatCallBack() ;
    std::function<void(MessageItem &, std::optional<string> &)> &getLastMsgCallback() ;
    std::function<void(int,std::optional<string>&)> &getCreateChatCallback() ;
    std::function<void(bool,std::optional<string>&)> &getDelChatCallback() ;
    std::function<void(Change&)> &getChatChangeCallback() ;
    std::function<void(Change&)>& getUnknownChatChangeCallback();
    std::function<void(inf::ChatRoom &,std::optional<string>&)>& getChatRoom();

private:
    std::optional<string> errString;
    std::vector<Chat> items;

    std::function<void(vector<ChatItem> &, std::optional<string> &)> chatCallback;
    std::function<void(MessageItem &, std::optional<string> &)>  lastMsgCallback;
    std::function<void(int,std::optional<string>&)> createChatCallback;
    std::function<void(bool,std::optional<string>&)> delChatCallback;
    std::function<void(Change&)> chatChangeCallback;
    std::function<void(Change&)> unknownChatChangeCallback;
    std::function<void(inf::ChatRoom &, std::optional<string>&)> chatRoom;
    std::function<void(inf::ChatRoom &, std::optional<string>&)> unknownChatRoomAdd;

signals:

public slots:
    void messageCreateByUser(const Msg &msg);
    void createChatByUser(const inf::ChatRoom &room);
    void unknownChatCreate(inf::ChatRoom &room);
};

#endif // GROUPMODEL_H
