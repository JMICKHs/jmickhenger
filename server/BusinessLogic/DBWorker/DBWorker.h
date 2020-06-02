#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/v_noabi/bsoncxx/exception/exception.hpp>

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
    AbstractDBWorker() = default;
    virtual void ChangeCollection(const std::string &collectionName) = 0;
    virtual int GetInt(const std::string &key) = 0;

    virtual bool GetBool(const std::string &key) = 0;

    virtual std::string GetStr(const std::string &key) = 0;
    virtual std::vector<std::string> GetStrVec(const std::string& key) = 0;

    virtual std::vector<int> GetIntVec(const std::string &key) = 0;

    virtual std::map<std::string, std::string> GetMap(const std::string &key) = 0;

    virtual void AddInt(const std::string &key, int data, bool flag = false) = 0;

    virtual void AddBool(const std::string &key, bool data, bool flag = false) = 0;

    virtual void AddStr(const std::string &key, const std::string &data, bool flag = false) = 0;

    virtual void AddStrVec(const std::string &key, const std::vector<std::string> &data, bool flag = false) = 0;

    virtual void AddIntVec(const std::string &key, const std::vector<int> &data, bool flag = false) = 0;

    virtual void AddMap(const std::string &key, const std::map<std::string, std::string> &data, bool flag = false) = 0;

    virtual void SaveDoc(bool flag) = 0;

    virtual bool NextDoc() = 0;

    virtual int UpdateDoc(const std::string &collect) = 0;

    virtual int DeleteDoc(const std::string &collect) = 0;

    virtual void DeleteCollect(const std::string &collect) = 0;

    virtual bool FindInt(const std::string &key, int lBoard, int rBoard) = 0;

    virtual bool FindStr(const std::string &key, const std::string &data) = 0;

    virtual bool FindBool(const std::string &key, bool val) = 0;

    virtual void Clear() = 0;

    virtual std::string GetJson() = 0;

    virtual std::string GetErrors() = 0;

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
    std::string error;

private:
    static std::string toString(bsoncxx::v_noabi::document::element elem);

public:
    DBWorker();
    DBWorker(const std::string& collectionName);
    void ChangeCollection(const std::string &collectionName) override;

    int GetInt(const std::string &key) override;

    bool GetBool(const std::string &key) override;

    std::string GetStr(const std::string &key) override;
    std::vector<std::string> GetStrVec(const std::string& key) override;

    std::vector<int> GetIntVec(const std::string &key) override;

    std::map<std::string, std::string> GetMap(const std::string &key) override;

    void AddInt(const std::string &key, int data, bool flag = false) override;

    void AddBool(const std::string &key, bool data, bool flag = false) override;

    void AddStr(const std::string &key, const std::string &data, bool flag = false) override;

    void AddStrVec(const std::string &key, const std::vector<std::string> &data, bool flag = false) override;

    void AddIntVec(const std::string &key, const std::vector<int> &data, bool flag = false) override;

    void AddMap(const std::string &key, const std::map<std::string, std::string> &data, bool flag = false) override;

    void SaveDoc(bool flag = false) override;

    bool NextDoc() override;

    int UpdateDoc(const std::string &collect) override;

    int DeleteDoc(const std::string &collect) override;

    void DeleteCollect(const std::string &collect) override;

    bool FindInt(const std::string &key, int lBoard, int rBoard = -1) override;

    bool FindBool(const std::string &key, bool val) override;

    bool FindStr(const std::string &key, const std::string &data) override;

    void Clear() override;

    std::string GetJson() override;

    std::string GetErrors() override;

    ~DBWorker() override = default;
};
