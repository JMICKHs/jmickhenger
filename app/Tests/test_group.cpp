#include <QtTest>
#include "test_group.h"

test_group::test_group()
    :MainWidget()
{

}

test_group::~test_group()
{

}

void test_group::test_gr1()
{
     QTest::mouseClick(ui->menuButton,Qt::LeftButton);
     QCOMPARE(this->menuWidget->isVisible(),1);

}

void test_group::test_gr2()
{
     QTest::mouseClick(ui->menuButton,Qt::LeftButton);
     int size = this->groupModel->getItems().size();
     this->menuWidget->getCreateWidget()->on_addFriend(3);
     this->menuWidget->getCreateWidget()->on_pushButton_2_clicked();
     int newSize = this->groupModel->getItems().size();
     QCOMPARE(size + 1,newSize);
}

void test_group::test_gr3()
{
//   QTest::mouseClick(this->menu,Qt::LeftButton);
//   QTest::mouseClick(this->menuWidget->getCreateButton(),Qt::LeftButton);
//   Chat chat;
//   chat.id =3;
//   chat.name = "testName";
//   chat.userIds = {0,3,2};
//   chat.lastMessage = "test";
//   emit this->menuWidget->createGroupSignal(chat);
//   std::list<QListWidgetItem*> items = this->getGroupList().getItems();

//   QString name = getGroupList().itemWidget(items.back())->findChild<QLabel*>("groupName")->text();
//   QString name = "";
//   QCOMPARE(name,chat.name);
}

void test_group::test_gr4()
{
//    QTest::mouseClick(this->menu,Qt::LeftButton);
//    QTest::mouseClick(this->menuWidget->getCreateButton(),Qt::LeftButton);
//    Chat chat;
//    chat.id =3;
//    chat.name = "testName";
//    chat.userIds = {0,3,2};
//    chat.lastMessage = "test";
//    emit this->menuWidget->createGroupSignal(chat);
//    std::list<QListWidgetItem*> items = this->getGroupList().getItems();

//   // QString lastMessage = getGroupList().itemWidget(items.back())->findChild<QLabel*>("lastMessage")->text();
//    QString lastMessage = "";
//    QCOMPARE(lastMessage,chat.lastMessage);
}

