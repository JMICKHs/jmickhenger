//
// Created by Sergei Alexeev on 13.04.2020.
//

#ifndef NETWORK_CACHE_INFO_H
#define NETWORK_CACHE_INFO_H

#include "Codeble.h"
#include <vector>
#include <string>

using namespace std;

namespace Info {

    class MyAccount : public Codeble {
    public:
        unsigned int id;
        string login;
        string password;
        vector<unsigned int> chats;
        string pathToAvatar;

        MyAccount(unsigned int id = 0,
                  string login = "",
                  string password = "",
                  vector<unsigned int> chats = vector<unsigned int>(0),
                  string pathToAvatar = "");

        string encode() override;

        void decode(string pathToJson) override;
    };

    class UserInfo {
    public:
    };

    class Message {
    public:
    private:
    };

    class ChatInfo {
    public:
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

#endif //NETWORK_CACHE_INFO_H
