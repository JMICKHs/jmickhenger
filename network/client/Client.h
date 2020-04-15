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

class AbstractClient {
public:
    AbstractClient()  = default;
    virtual void start() = 0;
    virtual void close() {}
    virtual Info::ChatChange cacthChage(int idChat, const function<void(const Info::ChatChange)>& callback) = 0;
    virtual Info::MyAccount login(string, string) = 0;
    virtual int registration(Info::MyAccount) = 0;
    virtual vector<Info::ChatInfo> getChatList(int idUser) = 0;
    virtual Info::ChatRoom getChatRoom(int idRoom) = 0;
    virtual vector<Info::Message> getMessages(int idChat, int begin, int end) = 0;
};

class Client : AbstractClient {
public:
    Client() = default;
    void start() {}
    void close() {}
    Info::ChatChange cacthChage(int idChat, const function<void(const Info::ChatChange)>& callback) {}
    Info::MyAccount login(string, string) {}
    int registration(Info::MyAccount) {}
    vector<Info::ChatInfo> getChatList(int idUser) {}
    Info::ChatRoom getChatRoom(int idRoom) {}
    vector<Info::Message> getMessages(int idChat, int begin, int end) {}
private:
    // сокет из буста ip::tcp::socket
    bool connect(int idUser) {}
    bool reconnect(int idUser) {}
    void sendRequest(char[]) {}
    void getResponse() {}
};


#endif //NETWORK_CLIENT_H
