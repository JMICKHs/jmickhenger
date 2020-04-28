//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_PARSER_H
#define NETWORK_PARSER_H


#include <string>
#include <vector>
#include "../info/Info.h"

using namespace std;

class AbstractParser {
public:
    AbstractParser() = default;
    virtual void createJson() = 0;
    virtual void setJson(const string & body) = 0;
    virtual string & getJson() = 0;
    virtual void setInt(const int & n, const string & name) = 0;
    virtual void setString(const string & n, const string & name) = 0;
    virtual void setDate(const string & n, const string & name) = 0;
    virtual void setBool(const bool & b, const string & name) = 0;
    virtual void setMatrixInt(const vector<int> & n, const string & name) = 0;
    virtual int & getInt(const string & name) = 0;
    virtual string & getString(const string & name) = 0;
    virtual int & getDate(const string & name) = 0;
    virtual bool & getBool(const string & name) = 0;
    virtual vector<int> & getMatrixInt(const string & name) = 0;
};

class Parser: public AbstractParser {
private:
    // boost::property_tree::ptree
public:
    Parser() {}
    ~Parser() {}
    std::string json;
    void createJson() {}
    void setJson(const string & body) {}
    string & getJson() { }
    void setInt(const int & n, const string & name) {}
    void setString(const string & n, const string & name) {}
    void setDate(const string & n, const string & name) {}
    void setBool(const bool & b, const string & name) {}
    void setMatrixInt(const vector<int> & n, const string & name) {}
    int & getInt(const string & name) {}
    string & getString(const string & name) {}
    int & getDate(const string & name) {}
    bool & getBool(const string & name) {}
    vector<int> & getMatrixInt(const string & name) {}
};


#endif //NETWORK_PARSER_H
