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
Q_DECLARE_METATYPE(inf::ChatRoom)

class GroupModel : public QAbstractListModel,public std::enable_shared_from_this<GroupModel>
{
    Q_OBJECT
public:
    GroupModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addItem(Chat &item);
    void setData(std::vector<ChatItem> &);
    void addCallbacks();
    void chatInfoSet(int id);

    std::function<void(std::vector<ChatItem> &, std::optional<std::string> &)> &getChatCallBack() ;
    std::function<void(MessageItem &, std::optional<std::string> &)> &getLastMsgCallback() ;
    std::function<void(int,std::optional<std::string>&)> &getCreateChatCallback() ;
    std::function<void(bool,std::optional<std::string>&)> &getDelChatCallback() ;
    std::function<void(Change&)> &getChatChangeCallback() ;
    std::function<void(Change&)>& getUnknownChatChangeCallback();
    std::function<void(Change&)>& getUnknownChatRoomAdd();
    std::function<void(inf::ChatRoom &,std::optional<std::string>&)>& getChatRoom();

    std::vector<Chat> getItems();
    int currChatId;

private:
    std::optional<std::string> errString;
    std::vector<Chat> items;

    std::function<void(std::vector<ChatItem> &, std::optional<std::string> &)> chatCallback;
    std::function<void(MessageItem &, std::optional<std::string> &)>  lastMsgCallback;
    std::function<void(MessageItem &, std::optional<std::string> &)>  lastMsgAndGetChat;
    std::function<void(int,std::optional<std::string>&)> createChatCallback;
    std::function<void(bool,std::optional<std::string>&)> delChatCallback;
    std::function<void(Change&)> chatChangeCallback;
    std::function<void(Change&)> unknownChatChangeCallback;
    std::function<void(inf::ChatRoom &, std::optional<std::string>&)> chatRoom;
    std::function<void(inf::ChatRoom &, std::optional<std::string>&)> newUnknownChatCallback;
    std::function<void(Change&)> unknownChatRoomAdd;
    std::function<void(inf::UserInfo &,std::optional<std::string>&)> userInfForMessage;

signals:
    void sendChatRoom(const inf::ChatRoom &inf);
    void sendNewMessages(std::vector<MessageItem> msgs);
    void updateItems();
public slots:
    void messageCreateByUser(const Msg &msg);
    void createChatByUser(const inf::ChatRoom &room);
    void unknownChatCreate(inf::ChatRoom &room);
};

#endif // GROUPMODEL_H
