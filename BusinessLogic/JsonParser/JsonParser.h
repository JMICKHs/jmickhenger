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
    virtual void SetNeededFile(std::string str) = 0;
    virtual int GetInt(std::string key) = 0;
    virtual std::string GetStr(std::string key) = 0;
    virtual std::vector<std::string> GetStrVec(std::string key) = 0;
    virtual std::map<std::string, std::string> GetMap(std::string key) = 0;
    virtual std::string CreateJson() = 0;
    virtual void AddInt(std::string key, int val) = 0;
    virtual void AddStr(std::string key, std::string val) = 0;
    virtual void AddStrVec(std::string key, std::vector<std::string> val) = 0;
    virtual void AddMap(std::string key, std::map<std::string, std::string> val) = 0;
    virtual ~AbstractJsonParser()= default;;
};

class JsonParser : AbstractJsonParser
{
    boost::property_tree::ptree root;

public:
    JsonParser();
    void SetNeededFile(std::string str) override;
    int GetInt(std::string key) override;
    std::string GetStr(std::string key) override;
    std::vector<std::string> GetStrVec(std::string key) override;
    std::map<std::string, std::string> GetMap(std::string key) override;
    std::string CreateJson() override ;
    void AddInt(std::string key, int val) override ;
    void AddStr(std::string key, std::string val) override ;
    void AddStrVec(std::string key, std::vector<std::string> val) override ;
    void AddMap(std::string key, std::map<std::string, std::string> val) override ;
    ~JsonParser() override = default;
};
