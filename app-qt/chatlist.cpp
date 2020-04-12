#include "chatlist.h"
#include <QDebug>

ChatList::ChatList(QWidget *parent)
    : QListWidget(parent)
{

}

std::vector<QListWidgetItem> ChatList::getItems()
{
    return items;
}

void ChatList::newMessage(const Message &message)
{
    QListWidgetItem item;
    item.setText(message.text);
    items.push_back(item);
}
