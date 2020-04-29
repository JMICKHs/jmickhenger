//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_CACHE_H
#define NETWORK_CACHE_H


#include "../info/Info.h"
#include <memory>
#include <optional>

class AbstractCache {
public:
    AbstractCache() = default;
    virtual bool save(inf::MyAccount & acc) = 0;
    virtual bool save(inf::UserInfo & user) = 0;
    virtual bool save(vector<inf::ChatInfo> & chatList) = 0;
    virtual std::optional<inf::MyAccount> & getMyAccount() = 0;
    virtual std::optional<inf::UserInfo> & getUser(int idUser) = 0;
    virtual vector<inf::ChatInfo> & getChatList() = 0;
};

class Cache: public AbstractCache {
public:
    Cache();
    ~Cache();
    bool save(inf::MyAccount & acc) override;
    bool save(inf::UserInfo & user) override;
    bool save(vector<inf::ChatInfo> & chatList) override;
    std::optional<inf::MyAccount> & getMyAccount() override;
    std::optional<inf::UserInfo> & getUser(int idUser) override;
    vector<inf::ChatInfo> & getChatList() override;
private:
    // sqlite3 db;
};


#endif //NETWORK_CACHE_H
