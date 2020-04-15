#pragma once

#include <string>
#include <vector>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class JsonParser
{
    boost::property_tree::ptree root;

public:
    void SetNeededFile(std::string str){};
    int GetInt(std::string key){};
    std::string GetStr(std::string key){};
    std::vector<std::string> GetStrVec(std::string key){};
    std::map<std::string, std::string> GetMap(std::string key){};
    std::string CreateJson();
    void AddInt(std::string key, int val);
    void AddStr(std::string key, std::string val);
    void AddStrVec(std::string key, std::vector<std::string> val);
    void AddMap(std::string key, std::map<std::string, std::string> val);
};
