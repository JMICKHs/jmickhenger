#ifndef GROUPLIST_H
#define GROUPLIST_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QFocusEvent>
#include <QString>
#include <netlib/info/Info.h>

using namespace inf;


class GroupList : public QListWidget
{
    Q_OBJECT


private:
    std::function<void(const ChatRoom chatroom)> ChatRoomCallback;
    std::function<void(const std::vector<ChatInfo>items)> ChatCallback;
    std::function<void(const ChatChange changeChat)> observerChat;

public:
    explicit GroupList(QWidget *parent = nullptr);
    std::list<QListWidgetItem *> getItems();

    void getChatById();
    void getItemsFromNet();

    std::function<void(const ChatRoom chatroom)> getChatRoomCallback() const;
    std::function<void(const std::vector<ChatInfo> items)> getChatCallback() const;
    std::function<void(const ChatChange changeChat)> getObserverChat() const;
};

#endif // GROUPLIST_H
