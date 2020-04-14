#include <QtTest>
#include "test_group.h"
#include "../mainwindow.h"

test_group::test_group()
{

}

test_group::~test_group()
{

}

void test_group::test_gr1()
{
    QTest::mouseClick(this->menu,Qt::LeftButton);
    QCOMPARE(this->menuWidget->isVisible(),1);

}

void test_group::test_gr2()
{
    std::list<QListWidgetItem*> items = this->getGroupList().getItems();
    int size = items.size();
    QTest::mouseClick(this->menu,Qt::LeftButton);
    QTest::mouseClick(this->menuWidget->getCreateButton(),Qt::LeftButton);
    std::list<QListWidgetItem*> newItems = this->getGroupList().getItems();
    int newSize = newItems.size();
    QCOMPARE(size + 1,newSize);
}

void test_group::test_gr3()
{
    QTest::mouseClick(this->menu,Qt::LeftButton);
    QTest::mouseClick(this->menuWidget->getCreateButton(),Qt::LeftButton);
    Chat chat;
    chat.id =3;
    chat.name = "testName";
    chat.userIds = {0,3,2};
    chat.lastMessage = "test";
    emit this->menuWidget->createGroupSignal(chat);
    std::list<QListWidgetItem*> items = this->getGroupList().getItems();

    QString name = getGroupList().itemWidget(items.back())->findChild<QLabel*>("groupName")->text();
    QCOMPARE(name,chat.name);
}

void test_group::test_gr4()
{
    QTest::mouseClick(this->menu,Qt::LeftButton);
    QTest::mouseClick(this->menuWidget->getCreateButton(),Qt::LeftButton);
    Chat chat;
    chat.id =3;
    chat.name = "testName";
    chat.userIds = {0,3,2};
    chat.lastMessage = "test";
    emit this->menuWidget->createGroupSignal(chat);
    std::list<QListWidgetItem*> items = this->getGroupList().getItems();

    QString lastMessage = getGroupList().itemWidget(items.back())->findChild<QLabel*>("lastMessage")->text();
    QCOMPARE(lastMessage,chat.lastMessage);
}

#include "test_group.moc"
