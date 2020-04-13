//
// Created by Sergei Alexeev on 13.04.2020.
//

#ifndef APP_CACHE_CACHE_H
#define APP_CACHE_CACHE_H

#include "info/Info.h"
#include <vector>

class Cache {
public:
    static Cache * shared();
    bool save(Info::MyAccount acc);
    bool save(Info::UserInfo user);
    bool save(vector<Info::ChatInfo> chatList);
    Info::MyAccount * getMyAccount();
    Info::UserInfo * getUser(int idUser);
    vector<Info::ChatInfo> getChatList();
private:
    // sqlite3 db;
    Cache * singleton;
    Cache();
};


#endif //APP_CACHE_CACHE_H
