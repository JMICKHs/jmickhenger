//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_APPNETWORK_H
#define NETWORK_APPNETWORK_H


#include "announcer/Announcer.h"
#include "client/Client.h"
#include "cache/Cache.h"
#include "info/Info.h"
#include <string>
#include <functional>
#include <vector>

using namespace std;

class AbstractNetwork {
public:
    AbstractNetwork() = default;
    Client clientDelegate;
    virtual Info::MyAccount * getMe() { return nullptr; }
    virtual void login(string name, string password, const function<void(const Info::MyAccount)>& callback) = 0;
    virtual void registration(Info::MyAccount acc, const function<void(const int)>& callback) = 0; //если id == 0, то неудачно
    virtual void getListChat(unsigned int idUser, const function<void(const vector<Info::ChatInfo>)>& callback) = 0;
    virtual void getChatRoom(unsigned int idChat, const function<void(const Info::ChatRoom)>& callback) = 0;
    virtual void setObserverChat(unsigned int idChat, const function<void(const Info::ChatChange)>& callback) = 0;
    virtual void sendMessage(Info::Message msg, const function<void(const bool)>& callback) = 0; // отправилось или нет bool
    virtual void getUser(unsigned int id, const function<void(const Info::UserInfo)>& callback) = 0;
    virtual void saveAvatar(string path, const function<void(const bool)>& callback) = 0;
    virtual void getMessages(int, int, int, const function<void(Info::Message[])>& callback) = 0;
    virtual void addChat(Info::ChatRoom, const function<void(Info::Message[])>& callback) = 0;
    virtual bool check() = 0;
};

class AppNetwork: AbstractNetwork {
public:
    ~AppNetwork();
    static AppNetwork * shared();
    Client clientDelegate;
    Info::MyAccount * getMe() { return nullptr; }
    void login(string name, string password, const function<void(const Info::MyAccount)>& callback) override;
    void registration(Info::MyAccount acc, const function<void(const int)>& callback) override;//если id == 0, то неудачно
    void getListChat(unsigned int idUser, const function<void(const vector<Info::ChatInfo>)>& callback) override;
    void getChatRoom(unsigned int idChat, const function<void(const Info::ChatRoom)>& callback) override;
    void setObserverChat(unsigned int idChat, const function<void(const Info::ChatChange)>& callback) override;
    void sendMessage(Info::Message msg, const function<void(const bool)>& callback) override; // отправилось или нет bool
    void getUser(unsigned int id, const function<void(const Info::UserInfo)>& callback) override;
    void saveAvatar(string path, const function<void(const bool)>& callback) override;// отправилось или нет bool
    void getMessages(int, int, int, const function<void(Info::Message[])>& callback) {}
    void addChat(Info::ChatRoom, const function<void(Info::Message[])>& callback) {}
    bool check();
private:
    static AppNetwork * singleton;
    Announcer announcer;
    Cache cache;
    AppNetwork();
};

#endif //NETWORK_APPNETWORK_H
