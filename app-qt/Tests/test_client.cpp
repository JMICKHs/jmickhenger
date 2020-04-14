#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include "../mainwindow.h"
#include <functional>

//struct UserInfo{
//    int i;
//    QString name;
//};
//using ::testing::AtLeast;
//using ::testing::Return;
//using ::testing::_;

//class AppNetwork{

//public:
//    virtual void getUser(unsigned int, const std::function<void(const UserInfo)> &) = 0;
//    virtual void getChatRoom(unsigned int, const std::function<void(const ChatRoom)> &) = 0;
//};

//class MockAppNetwork : public AppNetwork
//{
//public:
//  MOCK_METHOD2(getUser,void(unsigned int, const std::function<void(const UserInfo)>&));
//  MOCK_METHOD2(getChatRoom,void(unsigned int, const std::function<void(const ChatRoom)>&));
//};

//TEST( network, case1 ) {
//    MainWindow window;
//    MockAppNetwork mock;
//    window.searchById(3);

//    EXPECT_CALL(mock, getChatRoom(3,window.getGroupList().getChatRoomCallback)).WillOnce(Return(3));
//}
