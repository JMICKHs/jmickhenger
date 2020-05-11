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
    virtual void SetNeededFile(const std::string& filepath) = 0;
    virtual int GetInt(const std::string& key) = 0;
    virtual std::string GetStr(const std::string& key) = 0;
    virtual std::vector<std::string> GetStrVec(const std::string& key) = 0;
    virtual std::map<std::string, std::string> GetMap(const std::string& key) = 0;
    virtual std::string CreateFile(const std::string& col) = 0;
    virtual void AddInt(const std::string& key, int val) = 0;
    virtual void AddStr(const std::string& key, const std::string& val) = 0;
    virtual void AddStrVec(const std::string& key, const std::vector<std::string>& val) = 0;
    virtual void AddMap(const std::string& key, const std::map<std::string, std::string>& val) = 0;
    virtual ~AbstractDBWorker() = default;
};


class DBWorker : AbstractDBWorker
{
    mongocxx::client client;

public:
    DBWorker();
    void SetNeededFile(const std::string& filepath) override;
    int GetInt(const std::string& key) override;
    std::string GetStr(const std::string& key) override;
    std::vector<std::string> GetStrVec(const std::string& key) override;
    std::map<std::string, std::string> GetMap(const std::string& key) override;
    std::string CreateFile(const std::string& col) override;
    void AddInt(const std::string& key, int val) override;
    void AddStr(const std::string& key, const std::string& val) override;
    void AddStrVec(const std::string& key, const std::vector<std::string>& val) override;
    void AddMap(const std::string& key, const std::map<std::string, std::string>& val) override;
    ~DBWorker();
};
