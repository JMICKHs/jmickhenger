//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_PARSER_H
#define NETWORK_PARSER_H


#include <string>
#include <vector>
#include "../info/Info.h"


class Parser {
private:
    // boost::property_tree::ptree
public:
    Parser() {}
    std::string json;
    void createJson() {}
    void setJson(std::string body) {}
    void setInt(int n, std::string name) {}
    void setString(std::string n, std::string name) {}
    void setDate(std::string n, std::string name) {}
    void setBool(bool b, std::string name) {}
    void setMatrixInt(std::vector<int> n, std::string name) {}
    int getInt(std::string name) { return 0; }
    std::string getString(std::string name) { return "";}
    int getDate(std::string name) { return 0; }
    bool getBool(std::string name) { return false;}
    std::vector<int> setMatrixInt(std::string name) { return {};}
};


#endif //NETWORK_PARSER_H
