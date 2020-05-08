#ifndef CHATLIST_H
#define CHATLIST_H

#include <QListWidget>
#include <netlib/info/Info.h>

using namespace inf;
Q_DECLARE_METATYPE(Message)
class MessageWidget : public QWidget
{
    Q_OBJECT
    int id;
public:
    MessageWidget();
    int getId() const;
    void setId(int _id);
};

class ChatList : public QListWidget
{
    Q_OBJECT
private:
    std::function<void(std::vector<Message> items)> ChatCallback;

public:
    explicit ChatList(QWidget *parent = nullptr);

    std::list<QListWidgetItem*> getItems(); 
    void getItemsFromNet();
    std::function<void(std::vector<Message> items)> getChatCallback() const;

public slots:
    void newMessage(const Message& message);



};

#endif // CHATLIST_H
