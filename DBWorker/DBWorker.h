#pragma once

#include <vector>
#include <string>
#include <map>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/uri.hpp>


class DBInstanceSingleton
{
private:
    mongocxx::instance instance{};
    mongocxx::uri uri{};
    DBInstanceSingleton(){};
    DBInstanceSingleton(DBInstanceSingleton const&) = delete;
    DBInstanceSingleton& operator=(DBInstanceSingleton const&) = delete;

public:
    static DBInstanceSingleton& inctance()
    {
        static DBInstanceSingleton s;
        return s;
    }

    mongocxx::uri GetUri()
    {
        return std::move(uri);
    }
};


class DBWorker
{
    DBInstanceSingleton* instance;
    mongocxx::client client;

public:
    DBWorker(){};
    void SetNeededFile(std::string filepath);
    int GetInt(std::string key);
    std::string GetStr(std::string key);
    std::vector<std::string> GetStrVec(std::string key);
    std::map<std::string, std::string> GetMap(std::string key);
    std::string CreateFile(std::string col);
    void AddInt(std::string key, int val);
    void AddStr(std::string key, std::string val);
    void AddStrVec(std::string key, std::vector<std::string> val);
    void AddMap(std::string key, std::map<std::string, std::string> val);
    ~DBWorker(){};
};
