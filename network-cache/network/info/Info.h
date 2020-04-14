//
// Created by Sergei Alexeev on 13.04.2020.
//

#ifndef NETWORK_CACHE_INFO_H
#define NETWORK_CACHE_INFO_H

#include "Codeble.h"
#include <vector>
#include <string>
#include <ctime>

using namespace std;

namespace Info {

    class MyAccount: virtual Codeble {
    public:
        int id;
        string login;
        string pathToAvatar;
        string password;
        vector<int> chats;
        MyAccount() {}
        string encode() { return "NIL"; }
        void decode(string json) {}
    };

    class UserInfo: virtual Codeble {
    public:
        int id;
        string login;
        string pathToAvatar;
        UserInfo() {}
        string encode() { return "NIL"; }
        void decode(string json) {}
    };

    class Message: virtual Codeble {
    public:
        int chatId;
        int number;
        string text;
        int idOwner;
        time_t timesend;
        bool checked;
        Message() {}
        string encode() { return "NIL"; }
        void decode(string json) {}
    private:
    };

    class ChatInfo: virtual Codeble {
    public:
        int idChat;
        string name;
        ChatInfo(int id, string name) {}
        string encode() { return "NIL"; }
        void decode(string json) {}
    private:
    };

    class ChatRoom: virtual Codeble {
    public:
        string name;
        int idChat;
        vector<int> idUsers;
        vector<int> idAdmins;
        ChatRoom() {}
        string encode() { return "NIL"; }
        void decode(string json) {}
    private:
    };

    class ChatChange: Codeble {
    public:
        int idChat;
        string action;
        vector<Info::Message> messages;
        ChatChange() {}
        string encode() { return "NIL"; }
        void decode(string json) {}
    };

    class Reply: Codeble {
    public:
        string err;
        int status;
        int cmd;
        string body;
        Reply() {}
        string encode() { return "NIL"; }
        void decode(string json) {}
    };

}

#endif //NETWORK_CACHE_INFO_H
