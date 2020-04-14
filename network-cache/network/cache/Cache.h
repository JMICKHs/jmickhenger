//
// Created by Sergei Alexeev on 13.04.2020.
//

#ifndef NETWORK_CACHE_CACHE_H
#define NETWORK_CACHE_CACHE_H

#include "../info/Info.h"

class Cache {
public:
    Cache();
    bool save(Info::MyAccount acc);
    bool save(Info::UserInfo user);
    bool save(vector<Info::ChatInfo> chatList);
    Info::MyAccount * getMyAccount();
    Info::UserInfo * getUser(int idUser);
    vector<Info::ChatInfo> getChatList();
private:
    // sqlite3 db;
};



#endif //NETWORK_CACHE_CACHE_H
