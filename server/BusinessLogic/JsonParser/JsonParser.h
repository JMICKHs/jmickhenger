#pragma once

#include <string>
#include <vector>
#include <map>
#include <deque>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


class AbstractJsonParser
{
public:
    AbstractJsonParser(){};
    virtual void SetJson (const std::string& json) = 0;
    virtual void ParseDict(const std::string& key) = 0;
    virtual void MemorizePos() = 0;

    virtual void ForgotPos(int n) = 0;

    virtual void JumpToPos() = 0;
    virtual std::vector<int> GetIntVec() = 0;
    virtual std::vector<std::string> GetStrVec() = 0;
    virtual std::map<std::string, int> GetIntMap() = 0;
    virtual std::map<std::string, std::string> GetStrMap() = 0;
    virtual void ParseVec() = 0;

    virtual int GetInt(const std::string &key) = 0;

    virtual int GetBool(const std::string &key) = 0;

    virtual std::string GetStr(const std::string &key) = 0;
    virtual void CreateDict(const std::string& key = "") = 0;

    virtual void AddInt(int val) = 0;

    virtual void AddBool(bool val) = 0;

    virtual void AddVec(const std::string &key, const std::vector<int> &vec) = 0;
    virtual void AddMap(const std::string& key, const std::map<std::string, int>& m) = 0;

    virtual void AddPairInt(const std::string &key, int val) = 0;

    virtual void AddPairBool(const std::string &key, bool val) = 0;

    virtual void AddStr(const std::string &val) = 0;
    virtual void AddPairStr(const std::string& key, const std::string& val) = 0;
    virtual void BuildList(const std::string& key = "") = 0;
    virtual void BuildAll(const std::string& key = "") = 0;
    virtual std::string GetJson() = 0;
    virtual void Reverse() = 0;

    virtual void Clear() = 0;

    virtual void CompressStr(std::string &JsonStr) = 0;

    virtual ~AbstractJsonParser() = default;
};


class JsonParser : virtual AbstractJsonParser {
private:
    std::deque<boost::property_tree::ptree> docsStack;
    std::deque<int> posQueue;
    std::deque<std::string> namesQueue;
    unsigned int cntr;

public:
    JsonParser();

    void SetJson(const std::string &json) override;

    void ParseDict(const std::string &key) override;

    void MemorizePos() override;

    void ForgotPos(int n = 1) override;

    void JumpToPos() override;

    std::vector<int> GetIntVec() override;

    std::vector<std::string> GetStrVec() override;
    std::map<std::string, int> GetIntMap() override;
    std::map<std::string, std::string> GetStrMap() override;
    void ParseVec() override;

    int GetInt(const std::string &key) override;

    int GetBool(const std::string &key) override;

    std::string GetStr(const std::string &key) override;
    void CreateDict(const std::string& key = "") override;

    void AddInt(int val) override;

    void AddBool(bool val) override;

    void AddVec(const std::string &key, const std::vector<int> &vec) override;
    void AddMap(const std::string& key, const std::map<std::string, int>& m) override;

    void AddPairInt(const std::string &key, int val) override;

    void AddPairBool(const std::string &key, bool val) override;

    void AddStr(const std::string &val) override;
    void AddPairStr(const std::string& key, const std::string& val) override;
    void BuildList(const std::string& key = "") override;
    void BuildAll(const std::string& key = "") override;
    std::string GetJson() override;
    void Reverse() override;

    void Clear() override;

    void CompressStr(std::string &JsonStr) override;

    ~JsonParser() = default;
};
