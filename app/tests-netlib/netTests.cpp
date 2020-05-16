#include "gtest/gtest.h"

#include <iostream>
#include <ctime>

#include "AppNetwork.h"

using namespace inf;
using namespace std;


TEST(testAnnounser, test1) {
    Announcer an;
    int c = 0;
    auto testCallback = [&c](inf::ChatChange & change){
        ++c;
    };
    int idChat = 781;
    inf::Message msg(781, 903, "i am 903 msg in 781 chat from user id 67", 67, time(nullptr), false);
    inf::ChatChange testChange(idChat, "newMsg", {msg});
    an.addChatCallback(idChat, testCallback);
    an.notifyChat(testChange);
    ASSERT_EQ(1, c);
}

TEST(testAnnounser, test2) {
    Announcer an;
    int c = 0;
    auto testCallback = [&c](inf::ChatChange & change){
        ++c;
    };
    int idChat = 781;
    inf::Message msg(781, 903, "i am 903 msg in 781 chat from user id 67", 67, time(nullptr), false);
    inf::ChatChange testChange(idChat, "newMsg", {msg});
    an.addChatCallback(idChat, testCallback);
    int n = 78;
    for(size_t i = 0; i < n; ++i) {
        an.notifyChat(testChange);
    }
    ASSERT_EQ(c, n);
}

TEST(testAnnounser, test3) {
    Announcer an;
    int c = 0;
    auto testCallback = [&c](inf::ChatChange & change){
        ++c;
    };
    int idChat = 781;
    inf::Message msg(781, 903, "i am 903 msg in 781 chat from user id 67", 67, time(nullptr), false);
    int idOtherChat = 98;
    inf::ChatChange testChange(idOtherChat, "newMsg", {msg});
    an.addChatCallback(idChat, testCallback);
    int n = 78;
    for(size_t i = 0; i < n; ++i) {
        an.notifyChat(testChange);
    }
    ASSERT_EQ(c, 0);
}

TEST(testAnnounser, test4) {
    Announcer an;
    int c = 0;
    string context = "test4";
    int n = 89;
    int tmp = 0;
    function<void(int &)> testCallback = [&n](int & number) {
        number = n;
    };
    int cmd = 8;
    an.addCallback<string, int &>(cmd, context, testCallback);
    auto f = an.getCallback<string, int &>(cmd, context);
    ASSERT_EQ((bool)f, true);
    f.value()(tmp);
    ASSERT_EQ(tmp, n);
    f = an.getCallback<string, int &>(cmd, context);
    ASSERT_EQ((bool)f, false);
}

TEST(testAnnounser, test5) {
    Announcer an;
    int c = 0;
    string context = "test5";
    string otherContext = "blablabla";
    int n = 89;
    int tmp = 0;
    function<void(int &)> testCallback = [&n](int & number) {
        number = n;
    };
    int cmd = 8;
    an.addCallback<string, int &>(cmd, context, testCallback);
    auto f = an.getCallback<string, int &>(cmd, otherContext);
    ASSERT_EQ((bool)f, false);
}

TEST(testCodeble, test1) {
    string json = "{\n"
                  "    \"id\": \"5\",\n"
                  "    \"name\": \"testChat\"\n"
                  "}";
    ChatInfo info; info.decode(json);
    ASSERT_EQ(info.idChat,5);
    ASSERT_EQ(info.name, "testChat");
}

TEST(testCodeble, test2) {
    string json = "{\n"
                  "    \"id\": \"78\",\n"
                  "    \"login\": \"testUser\",\n"
                  "    \"password\": \"12345\",\n"
                  "    \"pathImage\": \"3\",\n"
                  "    \"chats\": [\n"
                  "        \"1\",\n"
                  "        \"189\",\n"
                  "        \"90\"\n"
                  "    ],\n"
                  "    \"friends\": [\n"
                  "        \"78\",\n"
                  "        \"90\",\n"
                  "        \"23\"\n"
                  "    ]\n"
                  "}";
    MyAccount acc; acc.decode(json);
    ASSERT_EQ(acc.id, 78);
    ASSERT_EQ(acc.login, "testUser");
    ASSERT_EQ(acc.password, "12345");
    vector<int> chatsTest = {1, 189, 90};
    for(size_t i = 0; i < acc.chats.size(); ++i) {
        ASSERT_EQ(acc.chats[i], chatsTest[i]);
    }
    vector<int> frndsTest = {78, 90, 23};
    for(size_t i = 0; i < acc.friends.size(); ++i) {
        ASSERT_EQ(acc.friends[i], frndsTest[i]);
    }
}
