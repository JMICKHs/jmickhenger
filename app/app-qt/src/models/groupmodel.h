#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include <QAbstractListModel>
#include "app-qt/src/custommbutton/custombutton.h"
#include <netlib/info/Info.h>
#include <functional>
#include <memory>
using ChatItem = inf::ChatInfo;
using Msg = inf::Message;
using Change = inf::ChatChange;

class Chat : public ChatItem{
public:
    QString lastMessage;
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

    const std::function<void(vector<ChatItem> &, std::optional<string> &)> &getChatCallBack() const ;
    std::function<void(Msg &, std::optional<string> &)> &getLastMsgCallback() ;
    std::function<void(int,std::optional<string>&)> &getCreateChatCallback() ;
    std::function<void(bool,std::optional<string>&)> &getDelChatCallback() ;
    std::function<void(Change&)> &getChatChangeCallback() ;

private:
    std::optional<string> errString;
    std::vector<Chat> items;

    std::function<void(vector<ChatItem> &, std::optional<string> &)> chatCallback;
    std::function<void(Msg &, std::optional<string> &)>  lastMsgCallback;
    std::function<void(int,std::optional<string>&)> createChatCallback;
    std::function<void(bool,std::optional<string>&)> delChatCallback;
    std::function<void(Change&)> chatChangeCallback;
signals:

public slots:
};

#endif // GROUPMODEL_H
