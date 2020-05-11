#pragma once

#include <string>
#include <vector>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


class AbstractJsonParser
{
public:
    AbstractJsonParser()= default;
    virtual void SetNeededFile(const std::string& str) = 0;
    virtual int GetInt(const std::string& key) = 0;
    virtual std::string GetStr(const std::string& key) = 0;
    virtual std::vector<std::string> GetStrVec(const std::string& key) = 0;
    virtual std::map<std::string, std::string> GetMap(const std::string& key) = 0;
    virtual std::string CreateJson() = 0;
    virtual void AddInt(const std::string& key, int val) = 0;
    virtual void AddStr(const std::string& key, const std::string& val) = 0;
    virtual void AddStrVec(const std::string& key, const std::vector<std::string>& val) = 0;
    virtual void AddMap(const std::string& key, const std::map<std::string, std::string>& val) = 0;
    virtual ~AbstractJsonParser()= default;;
};

class JsonParser : AbstractJsonParser
{
    boost::property_tree::ptree root;

public:
    JsonParser();
    void SetNeededFile(const std::string& str) override;
    int GetInt(const std::string& key) override;
    std::string GetStr(const std::string& key) override;
    std::vector<std::string> GetStrVec(const std::string& key) override;
    std::map<std::string, std::string> GetMap(const std::string& key) override;
    std::string CreateJson() override ;
    void AddInt(const std::string& key, int val) override ;
    void AddStr(const std::string& key, const std::string& val) override ;
    void AddStrVec(const std::string& key, const std::vector<std::string>& val) override ;
    void AddMap(const std::string& key, const std::map<std::string, std::string>& val) override ;
    ~JsonParser() override = default;
};
