#ifndef CHATLIST_H
#define CHATLIST_H

#include <QListWidget>

struct Message
{
public:
    int id;
    QString text;
};

class ChatList : public QListWidget
{
    Q_OBJECT
public:
    explicit ChatList(QWidget *parent = nullptr);
     std::vector<QListWidgetItem> getItems();

public slots:
    void newMessage(const Message& message);

private:
    std::vector<QListWidgetItem> items;

};

#endif // CHATLIST_H
