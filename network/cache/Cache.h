//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_CACHE_H
#define NETWORK_CACHE_H


#include "../info/Info.h"

class AbstractCache {
public:
    AbstractCache() = default;
    virtual bool save(Info::MyAccount acc) = 0;
    virtual bool save(Info::UserInfo user) = 0;
    virtual bool save(vector<Info::ChatInfo> chatList) = 0;
    virtual Info::MyAccount * getMyAccount() = 0;
    virtual Info::UserInfo * getUser(int idUser) = 0;
    virtual vector<Info::ChatInfo> getChatList() = 0;
};

class Cache: public AbstractCache {
public:
    Cache() {}
    bool save(Info::MyAccount acc) {}
    bool save(Info::UserInfo user) {}
    bool save(vector<Info::ChatInfo> chatList) {}
    Info::MyAccount * getMyAccount() { return nullptr; }
    Info::UserInfo * getUser(int idUser) { return nullptr; }
    vector<Info::ChatInfo> getChatList() { return {}; }
private:
    // sqlite3 db;
};


#endif //NETWORK_CACHE_H
