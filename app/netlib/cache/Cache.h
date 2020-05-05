//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_CACHE_H
#define NETLIB_CACHE_H


#include "../info/Info.h"
#include <memory>
#include <optional>

class AbstractCache {
public:
    virtual bool save(inf::MyAccount & acc) = 0;
    virtual bool save(inf::UserInfo & user) = 0;
    virtual bool save(vector<inf::ChatInfo> & chatList) = 0;
    virtual std::optional<inf::MyAccount> getMyAccount() = 0;
    virtual std::optional<inf::UserInfo> getUser(int idUser) = 0;
    virtual vector<inf::ChatInfo> getChatList() = 0;
};

class Cache: public AbstractCache {
public:
    Cache();
    bool save(inf::MyAccount & acc) override;
    bool save(inf::UserInfo & user) override;
    bool save(vector<inf::ChatInfo> & chatList) override;
    std::optional<inf::MyAccount> getMyAccount() override;
    std::optional<inf::UserInfo> getUser(int idUser) override;
    vector<inf::ChatInfo> getChatList() override;
private:
    // sqlite3 db;
};


#endif //NETLIB_CACHE_H
