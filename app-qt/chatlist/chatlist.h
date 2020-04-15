#ifndef CHATLIST_H
#define CHATLIST_H

#include <QListWidget>

struct Message
{
public:
    int id;
    QString text;
};
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
public:
    explicit ChatList(QWidget *parent = nullptr);
    std::list<QListWidgetItem*> getItems();
    void getItemsFromNet();
    std::function<void(std::vector<Message> items)> getChatCallback;

public slots:
    void newMessage(const Message& message);



};

#endif // CHATLIST_H
