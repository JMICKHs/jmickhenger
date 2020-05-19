//
// Created by Sergei Alexeev on 05.05.2020.
//

#include "Cache.h"

using namespace std;
using namespace inf;

map<int, UserInfo> Cache::users = map<int, UserInfo>();
optional<MyAccount> Cache::acc = nullopt;
string Cache::pathBd = "cache.db";
string Cache::userId = "ID";
string Cache::userName = "NAME";
string Cache::userAvatar = "AVATAR";
string Cache::userPassword = "PASS";
string Cache::tableUsers = "USERS";
string Cache::tableAccount = "ACCOUNT";

std::shared_ptr<Cache> Cache::shared() {
    static shared_ptr<Cache> single(new Cache);
    return single;
}

Cache::Cache() {
    rc = sqlite3_open(Cache::pathBd.data(), &db);
    if( rc != SQLITE_OK ) {
        cerr << "SQL error: \n" << zErrMsg;
        sqlite3_free(zErrMsg);
    }
}

Cache::~Cache() {
    clearTable(tableUsers);
    sqlite3_free(zErrMsg);
    sqlite3_close(db);
}

std::optional<inf::MyAccount> Cache::getMyAccount() {
    string request = "SELECT * from " + tableAccount;
    rc = sqlite3_exec(db, request.data(), &Cache::callbackUser, nullptr, &zErrMsg);
    if( rc != SQLITE_OK ) {
        sqlite3_free(zErrMsg);
        createAccount();
        return nullopt;
    }
    return acc;
}

void Cache::save(const MyAccount & me) {
    string request = "DELETE from " + tableAccount + "; " +
            "SELECT * from " + tableAccount;
    rc = sqlite3_exec(db, request.data(), nullptr, nullptr, &zErrMsg);
    if( rc != SQLITE_OK ) {
        sqlite3_free(zErrMsg);
        createAccount();
        save(me);
    } else {
        request = "INSERT INTO " + tableAccount + " (" + userId + ","
                + userName + "," + userAvatar + "," + userPassword + ")" +
                "VALUES (" + to_string(me.id) + ", '" + me.login +
                "' , '" + me.pathToAvatar +"', '" + me.password + "');";
        rc = sqlite3_exec(db, request.data(), nullptr, nullptr, &zErrMsg);
    }
}

void Cache::save(const inf::UserInfo & user) {
    removeUser(user.id);
    string request = "INSERT INTO " + tableUsers + " (" + userId + "," + userName + "," + userAvatar + ")" +
            "VALUES (" + to_string(user.id) + ", '" + user.login + "' , '" + user.pathToAvatar + "');";
    rc = sqlite3_exec(db, request.data(), nullptr, nullptr, &zErrMsg);
    if( rc != SQLITE_OK ) {
        createUsers();
        sqlite3_free(zErrMsg);
        save(user);
    }
}

std::optional<inf::UserInfo> Cache::getUser(int id) {
    string request = "SELECT * from " + tableUsers + " where " + userId + "=" + to_string(id);
    rc = sqlite3_exec(db, request.data(), &Cache::callbackUser, nullptr, &zErrMsg);
    if( rc != SQLITE_OK ) {
        sqlite3_free(zErrMsg);
        createUsers();
        return nullopt;
    }
    if(users.count(id)) {
        return users[id];
    } else {
        return nullopt;
    }
}

void Cache::removeUser(int id) {
    string sql = "DELETE from " + tableUsers + " where " + userId + "=" + to_string(id) + "; " +
            "SELECT * from " + tableUsers;
    rc = sqlite3_exec(db, sql.data(), nullptr, nullptr, &zErrMsg);
}

int Cache::callbackUser(void *data, int argc, char **argv, char **azColName) {
    int i;
    UserInfo user;
    for(i = 0; i < argc; i++) {
        if(userId == azColName[i]) {
            user.id = atoi(argv[i]);
        } else if (userName == azColName[i]) {
            user.login = argv[i];
        } else if (userAvatar == azColName[i]) {
            user.pathToAvatar = argv[i];
            users[user.id] = user;
        } else if (userPassword == azColName[i]) {
            MyAccount tmpAcc;
            tmpAcc.id = user.id;
            tmpAcc.login = user.login;
            tmpAcc.pathToAvatar = user.pathToAvatar;
            tmpAcc.password = argv[i];
            acc = move(tmpAcc);
        }
    }
    return 0;
}

void Cache::createAccount() {
    string request = "CREATE TABLE " + tableAccount + "(" +
                     userId + "       INT PRIMARY KEY  NOT NULL," +
                     userName + "     TEXT             NOT NULL," +
                     userAvatar + "   TEXT             NOT NULL," +
                     userPassword + " TEXT             NOT NULL);";
        rc = sqlite3_exec(db, request.data(), nullptr, nullptr, &zErrMsg);
        if( rc != SQLITE_OK ) {
            cerr << "SQL error: \n" << zErrMsg;
            sqlite3_free(zErrMsg);
        }
}

void Cache::createUsers() {
    string request = "CREATE TABLE " + tableUsers + "(" +
                     userId + "     INT PRIMARY KEY  NOT NULL," +
                     userName + "   TEXT             NOT NULL," +
                     userAvatar + " TEXT             NOT NULL);";
    rc = sqlite3_exec(db, request.data(), nullptr, nullptr, &zErrMsg);
    if( rc != SQLITE_OK ) {
        cerr << "SQL error: \n" << zErrMsg;
        sqlite3_free(zErrMsg);
    }
}

void Cache::clearTable(const std::string &table) {
    string sql = "DELETE from " + table + "; " +
                "SELECT * from " + table;
    rc = sqlite3_exec(db, sql.data(), nullptr, nullptr, &zErrMsg);
    if( rc != SQLITE_OK ) {
        cerr << "SQL error: \n" << zErrMsg;
        sqlite3_free(zErrMsg);
    }
}

