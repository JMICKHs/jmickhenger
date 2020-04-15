#include "gtest/gtest.h"
#include "../cache/Cache.h"
#include "string"
#include "vector"
#include "../client/Client.h"
#include "../AppNetwork.h"


TEST(cache, test1) {
    Cache cache;
    Info::MyAccount info;
    info.pathToAvatar = "/default";
    info.login = "test";
    info.chats = {};
    info.id = 404;
    info.password = "1234";
    cache.save(info);
    Info::MyAccount * test = cache.getMyAccount();
    if (test == nullptr) {
        ASSERT_EQ(test == nullptr, false);
    } else {
        ASSERT_EQ(info.id, test->id);
        ASSERT_EQ(info.login, test->login);
        ASSERT_EQ(info.pathToAvatar, test->pathToAvatar);
        ASSERT_EQ(info.chats, test->chats);
    }
}

TEST(cache, test2) {
    Cache cache;
    Info::UserInfo u1;
    Info::UserInfo u2;
    u1.id = 203;
    u1.login = "203";
    u1.pathToAvatar = "/default";
    u2.id = 204;
    u2.login = "204";
    u2.pathToAvatar = "/default2";
    cache.save(u1);
    cache.save(u2);
    Info::UserInfo * test = cache.getUser(204);
    if (test == nullptr) {
        ASSERT_EQ(test == nullptr, false);
    } else {
        ASSERT_EQ(u2.id, test->id);
        ASSERT_EQ(u2.login, test->login);
        ASSERT_EQ(u2.pathToAvatar, test->pathToAvatar);
    }

    test = cache.getUser(203);
    if (test == nullptr) {
        ASSERT_EQ(test == nullptr, false);
    } else {
        ASSERT_EQ(u1.id, test->id);
        ASSERT_EQ(u1.login, test->login);
        ASSERT_EQ(u1.pathToAvatar, test->pathToAvatar);
    }
}

TEST(cache, test3) {
    Cache cache;
    Info::ChatInfo i1(1, "test1");
    Info::ChatInfo i2(2, "test2");
    Info::ChatInfo i3(1, "test3");
    vector<Info::ChatInfo> vec = {i1, i2, i3};
    cache.save(vec);
    vector<Info::ChatInfo> test = cache.getChatList();
    ASSERT_EQ(test.size(), vec.size());
    for(size_t i = 0; i < vec.size(); ++i) {
        ASSERT_EQ(vec[i].idChat, test[i].idChat);
        ASSERT_EQ(vec[i].name, test[i].name);
    }

}

TEST(announcer, test1) {
    int counter = 0;
    function<void(const Info::ChatChange)> f = [&counter](const Info::ChatChange change) {counter++;};
    Announcer announcer;
    announcer.addCallback(3, f);
    announcer.addCallback(4, f);
    announcer.addCallback(5, f);
    Info::ChatChange change;
    change.idChat = 5;
    announcer.notify(change);
    announcer.notify(change);
    announcer.notify(change);
    announcer.notify(change);
    change.idChat = 7;
    announcer.notify(change);
    announcer.notify(change);
    announcer.notify(change);
    announcer.notify(change);
    change.idChat = 3;
    announcer.notify(change);
    announcer.notify(change);
    announcer.notify(change);
    announcer.notify(change);
    ASSERT_EQ(counter, 8);
}

TEST(codeble, test1) {
    string json = "{"
                  "\"name\": \"TEST\""
                  "\"idChat\": \"20\""
                  "}";
    Info::ChatInfo info1(20, "TEST");
    Info::ChatInfo info2(0, "nil");
    info2.decode(json);

    ASSERT_EQ(info1.idChat, info2.idChat);
    ASSERT_EQ(info1.name, info2.name);
}

TEST(codeble, test2) {
    string json = "{"
                  "\"name\": \"TEST\""
                  "\"id\": 20"
                  "\"pathToAvatar\": \"\""
                  "}";
    Info::UserInfo info1;
    info1.id = 20;
    info1.login = "TEST";
    info1.pathToAvatar = "";
    Info::UserInfo info2;
    info2.decode(json);

    ASSERT_EQ(info1.id, info2.id);
    ASSERT_EQ(info1.login, info2.login);
    ASSERT_EQ(info1.pathToAvatar, info2.pathToAvatar);
}

TEST(codeble, test3) {
    string json = "{"
                  "\"err\": \"\""
                  "\"cmd\": 2"
                  "\"status\": 0"
                  "\"err\": \"{}\""
                  "}";
    Info::Reply info1;
    info1.err = "";
    info1.cmd = 2;
    info1.status = 0;
    info1.body = "{}";
    Info::Reply info2;
    info2.decode(json);

    ASSERT_EQ(info1.err, info2.err);
    ASSERT_EQ(info1.cmd, info2.cmd);
    ASSERT_EQ(info1.status, info2.status);
    ASSERT_EQ(info1.body, info2.body);
}

TEST(codeble, test4) {
    string json = "{"
                  "\"idChat\": 22"
                  "\"name\": \"test\""
                  "\"idUsers\": [3, 4, 506]"
                  "\"idAdmins\": [3]"
                  "}";
    Info::ChatRoom info1;
    info1.idChat = 22;
    info1.name = "test";
    info1.idUsers = {3, 4, 506};
    info1.idAdmins = {3};
    Info::ChatRoom info2;
    info2.decode(json);

    ASSERT_EQ(info1.idChat, info2.idChat);
    ASSERT_EQ(info1.name, info2.name);
    ASSERT_EQ(info1.idUsers, info2.idUsers);
    ASSERT_EQ(info1.idAdmins, info2.idAdmins);
}
TEST(codeble, test5) {
    // проверить ChatChange
}

TEST(codeble, test6) {
    // проверить MyAccount
}

TEST(codeble, test7) {
    // проверить UserInfo
}

TEST(codeble, test8) {
    // проверить Message
}
//
//////мок для Client
////
////class MockClient : public Client {
////public:
////    MockClient() {}
////    ~MockClient();
////private:
////};
////
////TEST(network, test1) {
////    AppNetwork * net = AppNetwork::shared();
////    net->clientDelegate = MockClient();
////    ASSERT_EQ(true, true);
//}