#include "chatlist.h"
#include <QDebug>
#include <QLabel>
ChatList::ChatList(QWidget *parent)
    : QListWidget(parent)
{
    getChatRoomCallback = [](std::vector<Message> &items){};
}

std::list<QListWidgetItem*> ChatList::getItems()
{
    std::list<QListWidgetItem*> listItems;
    for(int i = 0; i < this->count(); ++i){
        listItems.push_back(this->item(i));
    }
    qDebug()<<itemWidget(listItems.back())->findChild<QLabel*>("text")->text();
    return listItems;
}

void ChatList::getItemsFromNet()
{

}
void ChatList::newMessage(const Message &message)
{
}


MessageWidget::MessageWidget()
{

}

int MessageWidget::getId() const
{
    return id;
}

void MessageWidget::setId(int _id)
{
    id = _id;
}
