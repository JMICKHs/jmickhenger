#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include "../mainwidget.h"
#include <functional>

using namespace  std;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

//class AppNetwork{
//
//public:
//   void getMessages(int id, std::function<void( std::function<void(std::vector<Message>)>)> func);
//   void getChatRoom(int id, std::function<void(const ChatRoom)> func );
//   void getListChat(int id, std::function<void( std::function<void(std::vector<ChatInfo>)>)> func);
//};
//
//class MockAppNetwork : public AppNetwork
//{
//public:
//  MOCK_METHOD2(getMessages,void(int id,  std::function<void( std::function<void(std::vector<Message> )>)> func));
//  MOCK_METHOD2(getChatRoom,void(int id ,  std::function<void(const ChatRoom )> func));
//  MOCK_METHOD2(getListChat,void(int id, std::function<void( std::function<void(std::vector<ChatInfo> )>)> func));
//
//};
//template<typename T, typename... U>
//
//size_t getAddress(std::function<T(U...)> f) {
//    typedef T(fnType)(U...);
//    fnType ** fnPointer = f.template target<fnType*>();
//    return (size_t) *fnPointer;
//}

MATCHER_P(data1AreEqual, parg ,"") { return (getAddress(arg) == getAddress(parg)); }

TEST( network, caseGroupCall ) {
//    MainWidget window;

//    MockAppNetwork mock;
//    window.client = &mock;
//    std::function<void(const ChatRoom)> func = window.getGroupList().getChatRoomCallback();
//    int a = 3;
//    EXPECT_CALL(mock, getChatRoom(a,data1AreEqual(func))).Times(1);
//    window.searchById(3);
}


TEST( network, caseMessageCall ) {
//    MainWidget window;

//    MockAppNetwork mock;
//    window.client = &mock;
//    std::function<void(std::vector<Message>)> func = window.getChatList().getChatCallback();
//    int a = 3;
//    EXPECT_CALL(mock, getMessages(a,data1AreEqual(func))).Times(1);
//    Message message;
//    window.createMessage(message);
}

TEST( network, caseChatInfoCall ) {
//    MainWidget window;

//    MockAppNetwork mock;
//    window.client = &mock;
//    std::function<void(std::vector<ChatInfo>)> func = window.getGroupList().getChatCallback();
//    int a  = 3;
//    EXPECT_CALL(mock, getMessages(a,data1AreEqual(func))).Times(1);
//    Message message;
//    window.getGroupList().getChatById();
}
