#include "gtest/gtest.h"
#include "../network/cache/Cache.h"
#include "string"
#include "../network/info/Info.h"
#include "../network/client/Client.h"
#include "../network/AppNetwork.h"


TEST(cache, test1) {
    ASSERT_EQ(true, true);
}

TEST(announcer, test1) {
    ASSERT_EQ(true, true);
}

TEST(codeble, test1) {
    // это пример для одной структуры
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

//мок для Client

class MockClient : public Client {
public:
    MockClient() {}
    ~MockClient();
private:
};

TEST(network, test1) {
    AppNetwork * net = AppNetwork::shared();
    net->clientDelegate = MockClient();
    ASSERT_EQ(true, true);
}