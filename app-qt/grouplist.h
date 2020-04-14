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

struct chatinfo{};

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

public:
    std::function<void(const ChatRoom chatroom)> getChatRoomCallback;
    std::function<void(std::vector<chatinfo> &items)> getChatCallback;

public:
    explicit GroupList(QWidget *parent = nullptr);
    std::list<QListWidgetItem *> getItems();
    void getChatById();
    void getItemsFromNet();

};

#endif // GROUPLIST_H
