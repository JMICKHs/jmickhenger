//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H


#include "string"
#include <vector>
#include <functional>
#include "../info/Info.h"
using namespace std;
using namespace inf;

class AbstractClient {
public:
    AbstractClient()  = default;
    virtual void start() = 0;
    virtual void close() = 0;
    virtual ChatChange & observerChatChange(const int & idChat, const function<void(const ChatChange)>& callback) = 0;
    virtual MyAccount & login(const string & nickname, const string & password) = 0;
    virtual const int & registration(inf::MyAccount & acc) = 0;
    virtual vector<ChatInfo> & getChatList(const int & idUser) = 0;
    virtual ChatRoom & getChatRoom(const int & idRoom) = 0;
    virtual vector<Message> & getMessages(const int & idChat, const int & begin, const int & end) = 0;
};

class Client : public AbstractClient {
public:
    Client() = default;
    void start() {}
    void close() {}
    ChatChange & observerChatChange(const int & idChat, const function<void(const ChatChange)>& callback) {}
    MyAccount & login(const string & nickname, const string & password) {}
    const int & registration(inf::MyAccount & acc) {}
    vector<ChatInfo> & getChatList(const int & idUser) {}
    ChatRoom & getChatRoom(const int & idRoom) {}
    vector<Message> & getMessages(const int & idChat, const int & begin, const int & end) {}
private:
    // сокет из буста ip::tcp::socket
    bool connect(int idUser) {}
    bool reconnect(int idUser) {}
    void sendRequest(char[]) {}
    void getResponse() {}
};


#endif //NETWORK_CLIENT_H
