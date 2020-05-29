#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include "app-qt/src/mainwidget/mainwidget.h"
#include <functional>

using namespace  std;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

class AppNetwork{

public:
   void getMessages(int id, std::function<void( std::function<void(std::vector<Message>)>)> func);
   void getChatRoom(int id, std::function<void(inf::ChatRoom&,std::optional<std::string>&)> func );
   void getListChat(int id, std::function<void( std::function<void(std::vector<ChatInfo>)>)> func);
};

class MockAppNetwork : public AppNetwork
{
public:
  MOCK_METHOD2(getMessages,void(int id,  std::function<void( std::function<void(std::vector<Message> )>)> func));
  MOCK_METHOD2(getChatRoom,void(int id , std::function<void(inf::ChatRoom &,std::optional<std::string>&)> func));
  MOCK_METHOD2(getListChat,void(int id, std::function<void( std::function<void(std::vector<ChatInfo> )>)> func));

};
template<typename T, typename... U>

size_t getAddress(std::function<T(U...)> f) {
    typedef T(fnType)(U...);
    fnType ** fnPointer = f.template target<fnType*>();
    return (size_t) *fnPointer;
}

MATCHER_P(data1AreEqual, parg ,"") { return (getAddress(arg) == getAddress(parg)); }

TEST( network, caseGroupCall ) {
    MockAppNetwork mock;
    GroupModel model;
    ChatRoom room;
    room.idChat =3;
    model.sendChatRoom(room);
    int a = 3;
    EXPECT_CALL(mock, getChatRoom(a,data1AreEqual(model.getChatRoom()))).Times(1);

}


TEST( network, caseMessageCall ) {
    ChatModel model;
    MainWidget window;
    MockAppNetwork mock;
    int a = 3;
    EXPECT_CALL(mock, getMessages(a,data1AreEqual(model.getChatCallback()))).Times(1);
    Message message;
    message.chatId = 3;
    window.sendMessageFromInput_s(message);
}

TEST( network, caseChatInfoCall ) {
    MainWidget window;
    GroupModel model;
    MockAppNetwork mock;
    int a  = 3;
    EXPECT_CALL(mock, getMessages(a,data1AreEqual(model.getChatCallBack()))).Times(1);
    ChatRoom chat;
    chat.idChat = 3;
    model.createChatByUser(chat);
}
