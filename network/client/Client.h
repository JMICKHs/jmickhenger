//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H


#include "string"
#include <vector>
#include "../info/Info.h"
using namespace std;

class Client {
public:
    Client() {}
    void start() {}
    void close() {}
    Info::ChatChange cacthChage() {}
    Info::MyAccount login(string, string) {}
    int registartion(Info::MyAccount) {}
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
