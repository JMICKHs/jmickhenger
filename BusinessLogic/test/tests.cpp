#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SupportStructures/SupportSructures.h"
#include "../JsonParser/JsonParser.h"
#include "../DBWorker/DBWorker.h"
#include "../Services/Services.h"
#include "../Business-Logic/Business-Logic.h"
#include "../Services/Services.cpp"
#include "../Business-Logic/Business-Logic.cpp"
#include <string>
#include <vector>
#include <map>
#include <queue>

using ::testing::Return;
using ::testing::_;


class DBWorkerMock : public AbstractDBWorker
{
public:

    MOCK_METHOD1(SetNeededFile, void(std::string filepath));
    MOCK_METHOD1(GetInt, int(std::string key));
    MOCK_METHOD1(GetStr, std::string(std::string key));
    MOCK_METHOD1(GetStrVec, std::vector<std::string>(std::string key));
    MOCK_METHOD1(GetMap, std::map<std::string, std::string>(std::string key));
    MOCK_METHOD1(CreateFile, std::string(std::string col));
    MOCK_METHOD2(AddInt, void(std::string key, int val));
    MOCK_METHOD2(AddStr, void(std::string key, std::string val));
    MOCK_METHOD2(AddStrVec, void(std::string key, std::vector<std::string> val));
    MOCK_METHOD2(AddMap, void(std::string key, std::map<std::string, std::string> val));
};

class JsonParserMock : public AbstractJsonParser
{
public:

    MOCK_METHOD1(SetNeededFile, void(std::string str));
    MOCK_METHOD1(GetInt, int(std::string key));
    MOCK_METHOD1(GetStr, std::string(std::string key));
    MOCK_METHOD1(GetStrVec, std::vector<std::string>(std::string key));
    MOCK_METHOD1(GetMap, std::map<std::string, std::string>(std::string key));
    MOCK_METHOD0(CreateJson, std::string());
    MOCK_METHOD2(AddInt, void(std::string key, int val));
    MOCK_METHOD2(AddStr, void(std::string key, std::string val));
    MOCK_METHOD2(AddStrVec, void(std::string key, std::vector<std::string> val));
    MOCK_METHOD2(AddMap, void(std::string key, std::map<std::string, std::string> val));
};

TEST(service, test1)
{
    DBWorkerMock db;
    JsonParserMock jp;
    std::queue<ResponseStruct>* queue = nullptr;

    NewChatService<DBWorkerMock, JsonParserMock> abs(db, jp, queue);

    std::vector<std::string> vec = {"Alex", "Bob"};
    std::string str = "new_chat";

    EXPECT_CALL(db, CreateFile("TestChat")).Times(1);
    EXPECT_CALL(db, AddInt("ChatId", 5)).Times(1);
    EXPECT_CALL(db, AddStr("ChatName", str)).Times(1);
    EXPECT_CALL(db, AddStrVec("Members", vec)).Times(1);

    EXPECT_CALL(jp, GetStr("ChatName")).Times(1);
    EXPECT_CALL(jp, GetStrVec("Members")).Times(1);

    EXPECT_CALL(jp, AddStr("ChatId", "new_chat")).Times(1);
    EXPECT_CALL(jp, AddStr("Status", "OK")).Times(1);

    abs.LogicRealize();
}

TEST(service, test2)
{
    DBWorkerMock db;
    JsonParserMock jp;
    std::queue<ResponseStruct> *queue = nullptr;
    NewUserService<DBWorkerMock, JsonParserMock> abs(db, jp, queue);

    EXPECT_CALL(db, SetNeededFile("Users")).Times(1);
    EXPECT_CALL(db, AddStr(_, _)).Times(2);

    EXPECT_CALL(jp, GetStr(_)).Times(2);

    EXPECT_CALL(jp, AddStr("UserId", _)).Times(1);
    EXPECT_CALL(jp, AddStr("Status", "OK")).Times(1);

    abs.LogicRealize();
}

TEST(service, test3)
{
    DBWorkerMock db;
    JsonParserMock jp;
    std::queue<ResponseStruct>* queue = nullptr;
    LoginService<DBWorkerMock, JsonParserMock> abs(db, jp, queue);

    EXPECT_CALL(db, SetNeededFile("Users")).Times(1);
    EXPECT_CALL(db, GetStr(_)).Times(2);

    EXPECT_CALL(jp, GetStr(_)).Times(2);

    EXPECT_CALL(jp, AddStr("Status", "OK")).Times(1);

    abs.LogicRealize();
}

TEST(service, test4)
{
    DBWorkerMock db;
    JsonParserMock jp;
    std::queue<ResponseStruct>* queue = nullptr;
    LoadChatPartService<DBWorkerMock, JsonParserMock> abs(db, jp, queue);

    std::vector<std::string> vec = {"Alex", "Bob"};
    std::string str = "new_chat";

    EXPECT_CALL(db, SetNeededFile(_)).Times(1);
    EXPECT_CALL(db, GetInt("ChatId")).Times(1);
    EXPECT_CALL(db, GetStr(_));

    EXPECT_CALL(jp, GetInt("ChatId")).Times(1);
    EXPECT_CALL(jp, GetInt("Number")).Times(1);

    EXPECT_CALL(jp, AddStr(_, _));
    EXPECT_CALL(jp, AddStr("Status", "OK")).Times(1);

    abs.LogicRealize();
}

TEST(service, test5)
{
    DBWorkerMock db;
    JsonParserMock jp;
    std::queue<ResponseStruct>* queue = nullptr;
    NewMessageService<DBWorkerMock, JsonParserMock> abs(db, jp, queue);

    EXPECT_CALL(db, SetNeededFile(_)).Times(1);
    EXPECT_CALL(db, AddStr(_, _)).Times(3);

    EXPECT_CALL(jp, GetStr("ChatId")).Times(1);
    EXPECT_CALL(jp, GetStr(_)).Times(3);

    EXPECT_CALL(jp, AddStr(_, _)).Times(3);
    EXPECT_CALL(jp, AddStr("Status", "OK")).Times(1);

    abs.LogicRealize();
}

TEST(db, test1)
{
    DBWorker db;

    ASSERT_NO_THROW(DBWorker());
}

TEST(parser, test1)
{
    JsonParser jp;

    jp.SetNeededFile("{Int:5}");
    int num = jp.GetInt("Int");
    ASSERT_EQ(num, 5);
}

TEST(parser, test2)
{
    JsonParser jp;

    jp.SetNeededFile("{Str:abc}");
    std::string num = jp.GetStr("Str");
    std::string str = "abc";
    for (int i =0; i< 3;i++) {
        ASSERT_EQ(num[i], str[i]);
    }
}

TEST(logic, test1)
{
    JsonParserMock j;
    BusinessLogic<JsonParserMock> bl(j);

    EXPECT_CALL(j, SetNeededFile(_)).Times(1);
    EXPECT_CALL(j, GetStr(_)).Times(1);

    bl.SetRequest("kvnfk");
}