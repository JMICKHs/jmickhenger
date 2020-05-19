//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_INFO_H
#define NETLIB_INFO_H

#import <string>
#import <memory>

#include "../parser/Parser.h"

class Codeble {
public:
    Codeble();
    virtual std::string encode() const = 0;
    virtual void decode(const std::string & json) = 0;
protected:
    std::shared_ptr<AbstractParser> parser;
};

namespace inf {
    class MyAccount : public Codeble {
    public:
        MyAccount();
        MyAccount(int id,
                const std::string & nickname,
                const std::string & image,
                const std::string & pass,
                const std::vector<int> & chats,
                const std::vector<int> & friends);
        int id;
        std::string login;
        std::string avatar;
        std::string password;
        std::vector<int> chats;
        std::vector<int> friends;
        std::string encode() const override;
        void decode(const std::string & json) override;
        static const std::string nameId;
        static const std::string nameLogin;
        static const std::string nameAvatar;
        static const std::string namePassword;
        static const std::string nameChats;
        static const std::string nameFriends;
    };

    class UserInfo : public Codeble {
    public:
        UserInfo();
        UserInfo(int id, const std::string & login, const std::string & image);
        int id;
        std::string login;
        std::string avatar;
        std::string encode() const override;
        void decode(const std::string & json) override;
        static const std::string nameId;
        static const std::string nameLogin;
        static const std::string nameAvatar;
        static const std::string nameListFrnd;
    };

    class Message : public Codeble {
    public:
        Message();
        //ТУТ
        Message(int id, int n, const std::string & text, int owner, time_t send, bool check);
        int chatId;
        int number;
        std::string text;
        int idOwner;
        time_t timesend;
        bool checked;
        std::string encode() const override;
        void decode(const std::string & json) override;
        static const std::string nameId;
        static const std::string nameNumber;
        static const std::string nameText;
        static const std::string nameOwner;
        static const std::string nameTime;
        static const std::string nameCheck;
        static const std::string nameArr;
    };

    class ChatInfo : public Codeble {
    public:
        ChatInfo();
        ChatInfo(int id, const std::string & name);
        int idChat;
        std::string name;
        bool operator ==(const ChatInfo &other) const;
        std::string encode() const override;
        void decode(const std::string & json) override;
        static const std::string nameId;
        static const std::string nameChat;
        static const std::string nameChatList;
    };

    class ChatRoom : public Codeble {
    public:
        ChatRoom();
        ChatRoom(int id, const std::string & name, const std::vector<int> & users, const std::vector<int> & admins);
        int idChat;
        std::string name;
        std::vector<int> idUsers;
        std::vector<int> idAdmins;
        std::string encode() const override;
        void decode(const std::string & json) override;
        static const std::string nameId;
        static const std::string nameChat;
        static const std::string nameUsers;
        static const std::string nameAdmins;
        static const std::string nameStart;
        static const std::string nameEnd;
    };

    class ChatChange : public Codeble {
    public:
        ChatChange();
        ChatChange(int id, const std::string & cmd, const std::vector<inf::Message> & msgs);
        int idChat;
        std::string action;
        std::vector<Message> messages;
        std::string encode() const override;
        void decode(const std::string & json) override;
        static const std::string nameId;
        static const std::string nameCmd;
        static const std::string nameMsg;
    };

    class Reply : public Codeble {
    public:
        Reply();
        Reply(const std::string & ec, int stat, int cmd, const std::string & body);
        std::string err;
        int status;
        int cmd;
        std::string body;
        std::string encode() const override;
        void decode(const std::string & json) override;
        static const std::string nameErr;
        static const std::string nameStatus;
        static const std::string nameCmd;
        static const std::string nameBody;
    };

    class Query : public Codeble {
    public:
        Query();
        Query(int command, const std::string & essence);
        int cmd;
        std::string body;
        std::string encode() const override;
        void decode(const std::string & json) override;
        static const std::string nameCmd;
        static const std::string nameBody;
    };
}


#endif //NETLIB_INFO_H
