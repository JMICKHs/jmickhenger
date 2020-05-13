#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SupportStructures/SupportSructures.h"
#include "../JsonParser/JsonParser.h"
#include "../DBWorker/DBWorker.h"
#include "../Services/Services.hpp"
#include "../Business-Logic/Business-Logic.hpp"
#include <string>
#include <vector>
#include <map>
#include <queue>

using ::testing::Return;
using ::testing::_;


class DBWorkerMock : public AbstractDBWorker
{
public:

    MOCK_METHOD1(GetInt, int(const std::string& key));
    MOCK_METHOD1(GetStr, std::string(const std::string& key));
    MOCK_METHOD1(GetStrVec, std::vector<std::string>(const std::string& key));
    MOCK_METHOD1(GetMap, std::map<std::string, std::string>(const std::string& key));
    MOCK_METHOD3(AddInt, void(const std::string& key, int val, bool flag));
    MOCK_METHOD3(AddStr, void(const std::string& key, const std::string& val, bool flag));
    MOCK_METHOD3(AddStrVec, void(const std::string& key, const std::vector<std::string>& val, bool flag));
    MOCK_METHOD3(AddMap, void(const std::string& key, const std::map<std::string, std::string>& val, bool flag));
    MOCK_METHOD1(SaveDoc, void(bool flag));
    MOCK_METHOD0(NextDoc, void());
    MOCK_METHOD1(UpdateDoc, void(const std::string& collect));
    MOCK_METHOD1(DeleteDoc, void(const std::string& collect));
    MOCK_METHOD1(DeleteCollect, void(const std::string& collect));
    MOCK_METHOD3(Find, void(const std::string &key, int lBoard, int rBoard));
};


class JsonParserMock : public AbstractJsonParser
{
public:

    MOCK_METHOD1(SetJson, void(const std::string& json));
    MOCK_METHOD1(ParseDict, void(const std::string& key));
    MOCK_METHOD0(MemorizePos, void());
    MOCK_METHOD0(ForgotPos, void());
    MOCK_METHOD0(JumpToPos, void());
    MOCK_METHOD0(ParseVec, void());
    MOCK_METHOD1(GetInt, int(const std::string& key));
    MOCK_METHOD1(GetStr, std::string(const std::string& key));
    MOCK_METHOD0(GetStrVec, std::vector<std::string>());
    MOCK_METHOD0(GetIntVec, std::vector<int>());
    MOCK_METHOD0(GetIntMap, std::map<std::string, int>());
    MOCK_METHOD0(GetStrMap, std::map<std::string, std::string>());
    MOCK_METHOD1(CreateDict, void(const std::string& key));
    MOCK_METHOD2(AddPairInt, void(const std::string& key, int val));
    MOCK_METHOD2(AddPairStr, void(const std::string& key, const std::string& val));
    MOCK_METHOD2(AddVec, void(const std::string& key, const std::vector<int>& vec));
    MOCK_METHOD2(AddMap, void(const std::string& key, const std::map<std::string, int>& m));
    MOCK_METHOD1(AddInt, void(int val));
    MOCK_METHOD1(AddStr, void(const std::string& val));
    MOCK_METHOD1(BuildList, void(const std::string& key));
    MOCK_METHOD1(BuildAll, void(const std::string& key));
    MOCK_METHOD0(GetJson, std::string());
    MOCK_METHOD0(Reverse, void());
};

TEST(service, test1)
{
    DBWorkerMock db;
    JsonParserMock jp;
    std::shared_ptr<Queue<ResponseStruct>> queue = nullptr;

    NewChatService<DBWorkerMock, JsonParserMock> abs(db, jp, queue);

    std::vector<std::string> vec = {"Alex", "Bob"};
    std::string str = "new_chat";

    EXPECT_CALL(db, AddInt("ChatId", 5, false)).Times(1);
    EXPECT_CALL(db, AddStr("ChatName", str, false)).Times(1);
    EXPECT_CALL(db, AddStrVec("Members", vec, false)).Times(1);

    EXPECT_CALL(jp, GetStr("ChatName")).Times(1);
    EXPECT_CALL(jp, GetStrVec()).Times(1);

    EXPECT_CALL(jp, AddStr("new_chat")).Times(1);
    EXPECT_CALL(jp, AddStr("OK")).Times(1);

    abs.LogicRealize();
}

TEST(service, test2)
{
    DBWorkerMock db;
    JsonParserMock jp;
    std::shared_ptr<Queue<ResponseStruct>> queue = nullptr;
    NewUserService<DBWorkerMock, JsonParserMock> abs(db, jp, queue);

    EXPECT_CALL(db, AddStr(_, _, _)).Times(2);

    EXPECT_CALL(jp, GetStr(_)).Times(2);

    EXPECT_CALL(jp, AddStr(_)).Times(1);
    EXPECT_CALL(jp, AddStr("OK")).Times(1);

    abs.LogicRealize();
}

TEST(service, test3)
{
    DBWorkerMock db;
    JsonParserMock jp;
    std::shared_ptr<Queue<ResponseStruct>> queue = nullptr;
    LoginService<DBWorkerMock, JsonParserMock> abs(db, jp, queue);

    EXPECT_CALL(db, GetStr(_)).Times(2);

    EXPECT_CALL(jp, GetStr(_)).Times(2);

    EXPECT_CALL(jp, AddStr("OK")).Times(1);

    abs.LogicRealize();
}

TEST(service, test4)
{
    DBWorkerMock db;
    JsonParserMock jp;
    std::shared_ptr<Queue<ResponseStruct>> queue = nullptr;
    LoadChatPartService<DBWorkerMock, JsonParserMock> abs(db, jp, queue);

    std::vector<std::string> vec = {"Alex", "Bob"};
    std::string str = "new_chat";


    EXPECT_CALL(db, GetInt("ChatId")).Times(1);
    EXPECT_CALL(db, GetStr(_));

    EXPECT_CALL(jp, GetInt("ChatId")).Times(1);
    EXPECT_CALL(jp, GetInt("Number")).Times(1);

    EXPECT_CALL(jp, AddStr(_));
    EXPECT_CALL(jp, AddStr("OK")).Times(1);

    abs.LogicRealize();
}

TEST(service, test5)
{
    DBWorkerMock db;
    JsonParserMock jp;
    std::shared_ptr<Queue<ResponseStruct>> queue = nullptr;
    NewMessageService<DBWorkerMock, JsonParserMock> abs(db, jp, queue);

    EXPECT_CALL(db, AddStr(_, _, _)).Times(3);

    EXPECT_CALL(jp, GetStr("ChatId")).Times(1);
    EXPECT_CALL(jp, GetStr(_)).Times(3);

    EXPECT_CALL(jp, AddStr(_)).Times(3);
    EXPECT_CALL(jp, AddStr("OK")).Times(1);

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

    jp.SetJson("{Int:5}");
    int num = jp.GetInt("Int");
    ASSERT_EQ(num, 5);
}

TEST(parser, test2)
{
    JsonParser jp;

    jp.SetJson("{Str:abc}");
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

    EXPECT_CALL(j, SetJson(_)).Times(1);
    EXPECT_CALL(j, GetStr(_)).Times(1);

    bl.SetRequest("kvnfk");
}