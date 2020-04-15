//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_PARSER_H
#define NETWORK_PARSER_H


#include <string>
#include <vector>
#include "../info/Info.h"


class AbstractParser {
public:
    std::string json;
    AbstractParser() = default;
    virtual void createJson() = 0;
    virtual void setJson(std::string body) = 0;
    virtual void setInt(int n, std::string name) = 0;
    virtual void setString(std::string n, std::string name) = 0;
    virtual void setDate(std::string n, std::string name) = 0;
    virtual void setBool(bool b, std::string name) = 0;
    virtual void setMatrixInt(std::vector<int> n, std::string name) = 0;
    virtual int getInt(std::string name) = 0;
    virtual std::string getString(std::string name) = 0;
    virtual int getDate(std::string name) = 0;
    virtual bool getBool(std::string name) = 0;
    virtual std::vector<int> setMatrixInt(std::string name) = 0;
};

class Parser: public AbstractParser {
private:
    // boost::property_tree::ptree
public:
    Parser() {}
    ~Parser() {}
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
