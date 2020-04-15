#include "chatlist.h"
#include <QDebug>
#include <QLabel>
ChatList::ChatList(QWidget *parent)
    : QListWidget(parent)
{
    ChatCallback = [](std::vector<Message> items){};
    this->setStyleSheet(
                        "QListWidget{ outline: 0;}"
                        "QListWidget::item:hover{  background-color:  rgb(255, 255, 255);selection-color: transperent;}"
                        "QListWidget::item:selected{ background-color:  rgb(255, 255, 255);selection-color: transperent;}"
                       );
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

std::function<void (std::vector<Message> items)> ChatList::getChatCallback() const
{
    return ChatCallback;
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
