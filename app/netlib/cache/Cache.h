//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_CACHE_H
#define NETLIB_CACHE_H

#import <optional>

#include "../info/Info.h"

class AbstractCache {
public:
    virtual bool save(const inf::MyAccount & acc) = 0;
    virtual bool save(const inf::UserInfo & user) = 0;
    virtual bool save(const std::vector<inf::ChatInfo> & chatList) = 0;
    virtual std::optional<inf::MyAccount> getMyAccount() = 0;
    virtual std::optional<inf::UserInfo> getUser(int idUser) = 0;
    virtual std::vector<inf::ChatInfo> getChatList() = 0;
};

class Cache: public AbstractCache {
public:
    Cache();
    bool save(const inf::MyAccount & acc) override;
    bool save(const inf::UserInfo & user) override;
    bool save(const std::vector<inf::ChatInfo> & chatList) override;
    std::optional<inf::MyAccount> getMyAccount() override;
    std::optional<inf::UserInfo> getUser(int idUser) override;
    std::vector<inf::ChatInfo> getChatList() override;
private:
    // sqlite3 db;
};


#endif //NETLIB_CACHE_H
