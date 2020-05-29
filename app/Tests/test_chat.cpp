#include <QtTest>
#include "test_chat.h"
#include "app-qt/src/mainwidget/mainwidget.h"
#include "app-qt/src/models/chatmodel.h"
#include "app-qt/src/chatinput/chatinput.h"


test_chat::test_chat()
    :MainWidget()

{

}

test_chat::~test_chat()
{

}

void test_chat::test_case1()
{
     Chat chat;
     chat.idChat = 3;
     groupModel->addItem(chat);
     QTest::keyClicks(this->ui->messageInput, "");
     QTest::mouseClick(this->ui->sendButton,Qt::LeftButton);
     std::vector<Msg> items = this->chatModel->getItems();
     QString text = QString::fromStdString(items.back().text);

     QCOMPARE(text,"Send My Message");
}

void test_chat::test_case2()
{
     QTest::keyClicks(this->ui->messageInput, "");
     QTest::mouseClick(this->ui->sendButton,Qt::LeftButton);
     std::vector<Msg> items = this->chatModel->getItems();

     QCOMPARE(items.size(),0);
}

void test_chat::test_case3()
{
     QTest::keyClicks(this->ui->messageInput, "12312Message");
     QTest::mouseClick(this->ui->sendButton,Qt::LeftButton);
     std::vector<Msg> items = this->chatModel->getItems();
     QString text = QString::fromStdString(items.back().text);

     QCOMPARE(text,"12312Message");
}

#include "test_chat.moc"
