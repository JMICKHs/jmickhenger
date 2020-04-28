#ifndef GROUPLIST_H
#define GROUPLIST_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QFocusEvent>
#include <QString>


struct Chat{
   int id;
   std::vector<int> userIds;
   QString name;
   QString lastMessage;
};

struct ChatChange{};
struct ChatInfo{};
struct ChatRoom{
    QString name;
    int id;
    std::vector<int> userIds;
};

class GroupList : public QListWidget
{
    Q_OBJECT

public slots:
    void addNewGroup(Chat & chat);

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
