//
// Created by Sergei Alexeev on 11.04.2020.
//

#ifndef APP_NETWORK_INFO_H
#define APP_NETWORK_INFO_H

#endif //APP_NETWORK_INFO_H



#include <vector>
#include <string>

using namespace std;


// ДОБАВЛЕНЫ ДЛЯ ТЕСТОВ И РАБОТЫ, НАСТРОЯЩИЕ КЛАССЫ В ВЕТКЕ app-network
namespace Info {

    class UserInfo {
    public:
    };

    class MyAccount {
    public:
    };

    class Message {
    public:
    private:
    };

    class ChatInfo {
    public:
        int idChat;
        string nameChat;
        ChatInfo(int id, string name) {
            idChat = id;
            nameChat = name;
        }
    private:
    };

    class ChatRoom {
    public:
    private:
    };

    class ChatChange {
    public:
        unsigned int idChat;
    };
}