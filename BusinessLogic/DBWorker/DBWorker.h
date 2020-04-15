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

public:
    DBInstanceSingleton(DBInstanceSingleton const&) = delete;
    DBInstanceSingleton& operator=(DBInstanceSingleton const&) = delete;

    static DBInstanceSingleton& inctance()
    {
        static DBInstanceSingleton s;
        return s;
    }

    mongocxx::uri GetUri()
    {
        return std::move(uri);
    }

    DBInstanceSingleton()= default;
};

class AbstractDBWorker
{
public:
    AbstractDBWorker()= default;
    virtual void SetNeededFile(std::string filepath) = 0;
    virtual int GetInt(std::string key) = 0;
    virtual std::string GetStr(std::string key) = 0;
    virtual std::vector<std::string> GetStrVec(std::string key) = 0;
    virtual std::map<std::string, std::string> GetMap(std::string key) = 0;
    virtual std::string CreateFile(std::string col) = 0;
    virtual void AddInt(std::string key, int val) = 0;
    virtual void AddStr(std::string key, std::string val) = 0;
    virtual void AddStrVec(std::string key, std::vector<std::string> val) = 0;
    virtual void AddMap(std::string key, std::map<std::string, std::string> val) = 0;
    virtual ~AbstractDBWorker() = default;
};


class DBWorker : AbstractDBWorker
{
    mongocxx::client client;

public:
    DBWorker();
    void SetNeededFile(std::string filepath) override;
    int GetInt(std::string key) override;
    std::string GetStr(std::string key) override;
    std::vector<std::string> GetStrVec(std::string key) override;
    std::map<std::string, std::string> GetMap(std::string key) override;
    std::string CreateFile(std::string col) override;
    void AddInt(std::string key, int val) override;
    void AddStr(std::string key, std::string val) override;
    void AddStrVec(std::string key, std::vector<std::string> val) override;
    void AddMap(std::string key, std::map<std::string, std::string> val) override;
    ~DBWorker();
};
