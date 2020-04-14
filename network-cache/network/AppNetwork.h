//
// Created by Sergei Alexeev on 13.04.2020.
//

#ifndef NETWORK_CACHE_APPNETWORK_H
#define NETWORK_CACHE_APPNETWORK_H


#include "announcer/Announcer.h"
#include "client/Client.h"
#include "cache/Cache.h"
#include <string>
#include <functional>
#include <vector>

using namespace std;

class AppNetwork {
public:
    ~AppNetwork();
    static AppNetwork * shared();
    Client clientDelegate;
    Info::MyAccount * getMe() { return nullptr; }
    void login(string name, string password, const function<void(const Info::MyAccount)>& callback);
    void registration(Info::MyAccount acc, const function<void(const int)>& callback); //если id == 0, то неудачно
    void getListChat(unsigned int idUser, const function<void(const vector<Info::ChatInfo>)>& callback);
    void getChatRoom(unsigned int idChat, const function<void(const Info::ChatRoom)>& callback);
    void setObserverChat(unsigned int idChat, const function<void(const Info::ChatChange)>& callback);
    void sendMessage(Info::Message msg, const function<void(const bool)>& callback); // отправилось или нет bool
    void getUser(unsigned int id, const function<void(const Info::UserInfo)>& callback);
    void saveAvatar(string path, const function<void(const bool)>& callback); // отправилось или нет bool
    void getMessages(int, int, int, const function<void(Info::Message[])>& callback) {}
    void addChat(Info::ChatRoom, const function<void(Info::Message[])>& callback) {}
    bool check();
private:
    static AppNetwork * singleton;
    Announcer announcer;
    Cache cache;
    AppNetwork();
};



#endif //NETWORK_CACHE_APPNETWORK_H
