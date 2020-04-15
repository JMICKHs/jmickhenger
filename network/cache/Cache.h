//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_CACHE_H
#define NETWORK_CACHE_H


#include "../info/Info.h"

class Cache {
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
