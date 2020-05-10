//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_INFO_H
#define NETLIB_INFO_H


#include <vector>
#include <string>
#include <ctime>
#include <memory>
#include "../parser/Parser.h"

using namespace std;

class Codeble {
public:
    Codeble();
    virtual string encode() const = 0;
    virtual void decode(const string & json) = 0;
protected:
    shared_ptr<AbstractParser> parser;
};

namespace inf {
    class MyAccount : public Codeble {
    public:
        MyAccount();
        MyAccount(int id,
                const string & login,
                const string & image,
                const string & pass,
                const vector<int> & chats,
                const vector<int> & friends);
        int id;
        string login;
        string pathToAvatar;
        string password;
        vector<int> chats;
        vector<int> friends;
        string encode() const override;
        void decode(const string & json) override;
        static const string nameId;
        static const string nameLogin;
        static const string namePathImage;
        static const string namePassword;
        static const string nameChats;
        static const string nameFriends;
    };

    class UserInfo : public Codeble {
    public:
        UserInfo();
        UserInfo(int id, const string & login, const string & image);
        int id;
        string login;
        string pathToAvatar;
        string encode() const override;
        void decode(const string & json) override;
        static const string nameId;
        static const string nameLogin;
        static const string namePathImage;
    };

    class Message : public Codeble {
    public:
        Message();
        //ТУТ
        Message(int id, int n, const string & text, int owner, time_t send, bool check);
        int chatId;
        int number;
        string text;
        int idOwner;
        time_t timesend;
        bool checked;
        string encode() const override;
        void decode(const string & json) override;
        static const string nameId;
        static const string nameNumber;
        static const string nameText;
        static const string nameOwner;
        static const string nameTime;
        static const string nameCheck;
    };

    class ChatInfo : public Codeble {
    public:
        ChatInfo();
        ChatInfo(int id, const string & name);
        int idChat;
        string name;
        bool operator ==(const ChatInfo &other) const;
        string encode() const override;
        void decode(const string & json) override;
        static const string nameId;
        static const string nameChat;
    };

    class ChatRoom : public Codeble {
    public:
        ChatRoom();
        ChatRoom(int id, const string & name, const vector<int> & users, const vector<int> & admins);
        int idChat;
        string name;
        vector<int> idUsers;
        vector<int> idAdmins;
        string encode() const override;
        void decode(const string & json) override;
        static const string nameId;
        static const string nameChat;
        static const string nameUsers;
        static const string nameAdmins;
    };

    class ChatChange : public Codeble {
    public:
        ChatChange();
        ChatChange(int id, const string & cmd, const vector<inf::Message> & msgs);
        int idChat;
        string action;
        vector<Message> messages;
        string encode() const override;
        void decode(const string & json) override;
        static const string nameId;
        static const string nameCmd;
        static const string nameMsg;
    };

    class Package : public Codeble {
    public:
        Package();
        Package(const string & ec, int stat, int cmd, const string & body);
        string err;
        int status;
        int cmd;
        string body;
        string encode() const override;
        void decode(const string & json) override;
        static const string nameErr;
        static const string nameStatus;
        static const string nameCmd;
        static const string nameBody;
    };
}


#endif //NETLIB_INFO_H
