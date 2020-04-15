//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_INFO_H
#define NETWORK_INFO_H

#include <vector>
#include <string>
#include <ctime>
#include "../parser/Parser.h"

using namespace std;

class Codeble {
public:
    virtual string encode() = 0;
    virtual void decode(string json) = 0;
protected:
    Parser parser;
};

namespace Info {

    class MyAccount : virtual Codeble {
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

    class UserInfo : protected Codeble {
    public:
        int id;
        string login;
        string pathToAvatar;
        UserInfo() {}
        string encode() { return "NIL"; }
        void decode(string json) {}
    };

    class Message : protected Codeble {
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

    class ChatInfo : protected Codeble {
    public:
        int idChat;
        string name;
        ChatInfo() {}
        ChatInfo(int id, string name) {}
        string encode() { return "NIL"; }
        void decode(string json) {}
    private:
    };

    class ChatRoom : protected Codeble {
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

    class ChatChange : protected Codeble {
    public:
        int idChat;
        string action;
        vector<Message> messages;
        ChatChange() {}
        string encode() { return "NIL"; }
        void decode(string json) {}
    };

    class Reply : protected Codeble {
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


#endif //NETWORK_INFO_H
