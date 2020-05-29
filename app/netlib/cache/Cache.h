//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_CACHE_H
#define NETLIB_CACHE_H

#import <iostream>
#import <optional>
#import <map>

#include "../sqllite-src/sqlite3.h"

#include "../info/Info.h"


class AbstractCache {
public:
    virtual void clear() = 0;
    virtual void save(const inf::MyAccount & acc) = 0;
    virtual void save(const inf::UserInfo & user) = 0;
    virtual std::optional<inf::MyAccount> getMyAccount() = 0;
    virtual std::optional<inf::UserInfo> getUser(int idUser) = 0;
};

class Cache: public AbstractCache {
public:
    static std::shared_ptr<Cache> shared();
    Cache(const Cache & other) = delete;
    Cache(Cache && other) = delete;
    Cache & operator=(const Cache & other) = delete;
    Cache & operator=(Cache && other) = delete;
    ~Cache();
    void clear() override;
    void save(const inf::MyAccount & me) override;
    std::optional<inf::MyAccount> getMyAccount() override;
    void save(const inf::UserInfo & user) override;
    std::optional<inf::UserInfo> getUser(int idUser) override;
private: //поля
    sqlite3 * db;
    char * zErrMsg = nullptr;
    int rc;
    static std::map<int, inf::UserInfo> users;
    static std::optional<inf::MyAccount> acc;
    static std::string pathBd;
    static std::string tableUsers;
    static std::string tableAccount;
    static std::string userId;
    static std::string userName;
    static std::string userAvatar;
    static std::string userPassword;
private: //методы
    Cache();
    void removeUser(int id);
    static int callbackUser(void * data, int argc, char ** argv, char ** azColName);
    void createAccount();
    void createUsers();
    void clearTable(const std::string & table);
};

#endif //NETLIB_CACHE_H
