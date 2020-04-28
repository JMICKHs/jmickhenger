#include "test_showprofile.h"
#include <QtTest>

test_showprofile::test_showprofile()
{

}

test_showprofile::~test_showprofile()
{

}

void test_showprofile::test_ShowProfile1()
{
    QString mess{"12321Message"};
    QTest::keyClicks(this->textMessage, mess);
    QTest::mouseClick(this->send,Qt::LeftButton);
    std::list<QListWidgetItem*> items = chatList->getItems();
    QTest::mouseClick(chatList->itemWidget(items.back())->findChild<CustomButton*>("profile"),Qt::LeftButton);

    QCOMPARE( this->dataShow->isVisible(),1);
    this->textMessage->clear();
}

void test_showprofile::test_ShowProfile2()
{
    QString mess{"12321Message"};
    QTest::keyClicks(this->textMessage, mess);
    QTest::mouseClick(this->send,Qt::LeftButton);
    std::list<QListWidgetItem*> items = chatList->getItems();
    QTest::mouseClick(chatList->itemWidget(items.back())->findChild<CustomButton*>("profile"),Qt::LeftButton);

    int _id = dynamic_cast<MessageWidget*>(chatList->itemWidget(items.back()))->getId();

    int id = this->dataShow->getData().getId();

    QCOMPARE( id,_id);
    this->textMessage->clear();
}
