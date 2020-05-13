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
#include <bsoncxx/builder/stream/document.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;


class DBInstanceSingleton
{
private:
    mongocxx::instance instance{};

public:
    DBInstanceSingleton(DBInstanceSingleton const&) = delete;
    DBInstanceSingleton& operator=(DBInstanceSingleton const&) = delete;

    static DBInstanceSingleton& inctance()
    {
        static DBInstanceSingleton s;
        return s;
    }

    DBInstanceSingleton()= default;
};

class AbstractDBWorker
{
public:
    AbstractDBWorker()= default;
    virtual int GetInt(const std::string& key) = 0;
    virtual std::string GetStr(const std::string& key) = 0;
    virtual std::vector<std::string> GetStrVec(const std::string& key) = 0;
    virtual std::map<std::string, std::string> GetMap(const std::string& key) = 0;
    virtual void AddInt(const std::string& key, int val, bool flag = false) = 0;
    virtual void AddStr(const std::string& key, const std::string& val, bool flag = false) = 0;
    virtual void AddStrVec(const std::string& key, const std::vector<std::string>& val, bool flag = false) = 0;
    virtual void AddMap(const std::string& key, const std::map<std::string, std::string>& val, bool flag = false) = 0;
    virtual void SaveDoc(bool flag) = 0;
    virtual void NextDoc() = 0;
    virtual void UpdateDoc(const std::string& collect) = 0;
    virtual void DeleteDoc(const std::string& collect) = 0;
    virtual void DeleteCollect(const std::string& collect) = 0;
    virtual void Find(const std::string &key, int lBoard, int rBoard) = 0;
    virtual ~AbstractDBWorker() = default;
};


class DBWorker : virtual AbstractDBWorker
{
private:
    mongocxx::client client;
    mongocxx::collection collection;
    std::array<bsoncxx::builder::stream::document, 2> doc;
    std::optional<mongocxx::cursor> cur;
    bsoncxx::document::view res;
    const std::string dbName = "JHMICHs";

public:
    DBWorker() = delete;
    DBWorker(const std::string& collectionName);
    int GetInt(const std::string& key) override;
    std::string GetStr(const std::string& key) override;
    std::vector<std::string> GetStrVec(const std::string& key) override;
    std::map<std::string, std::string> GetMap(const std::string& key) override;
    void AddInt(const std::string& key, int val, bool flag = false) override;
    void AddStr(const std::string& key, const std::string& val, bool flag = false) override;
    void AddStrVec(const std::string& key, const std::vector<std::string>& val, bool flag = false) override;
    void AddMap(const std::string& key, const std::map<std::string, std::string>& val, bool flag = false) override;
    void SaveDoc(bool flag = false) override;
    void NextDoc() override;
    void UpdateDoc(const std::string& collect) override;
    void DeleteDoc(const std::string& collect) override;
    void DeleteCollect(const std::string& collect) override;
    void Find(const std::string &key, int lBoard, int rBoard = -1) override;
    ~DBWorker() override = default;
};
