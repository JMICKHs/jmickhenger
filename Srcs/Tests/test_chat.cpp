#include <QtTest>
#include "../mainwindow.h"



class test_chat : public MainWindow
{
    Q_OBJECT

public:
    test_chat();
    ~test_chat();



private slots:
    void test_case1();
    void test_case2();
    void test_case3();

};

test_chat::test_chat()
{
    createObjects();
    linkObjects();
}

test_chat::~test_chat()
{

}

void test_chat::test_case1()
{

    QTest::keyClicks(this->textMessage, "Send My Message");
    QTest::mouseClick(this->send,Qt::LeftButton);
    std::vector<QListWidgetItem> items = chatList->getItems();

    QCOMPARE(items[items.size() - 1].text(),"Send My Message");
    this->textMessage->clear();
}

void test_chat::test_case2()
{
    QTest::keyClicks(this->textMessage, "");
    QTest::mouseClick(this->send,Qt::LeftButton);
    std::vector<QListWidgetItem> items = chatList->getItems();

    QCOMPARE(items[items.size() - 1].text(),"");
    this->textMessage->clear();
}

void test_chat::test_case3()
{
    QString mess{"12321Message"};
    QTest::keyClicks(this->textMessage, mess);
    QTest::mouseClick(this->send,Qt::LeftButton);
    std::vector<QListWidgetItem> items = chatList->getItems();

    QCOMPARE(items[items.size() - 1].text(),"12321Message");
    this->textMessage->clear();
}


QTEST_MAIN(test_chat)
#include "test_chat.moc"
