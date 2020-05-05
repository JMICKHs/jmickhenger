//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_PARSER_H
#define NETLIB_PARSER_H


#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>

using namespace std;
namespace bptree = boost::property_tree;

class AbstractParser {
public:
    virtual void addBool(const bool & value, const string & name) = 0;
    virtual void addInt(const int & value, const string & name) = 0;
    virtual void addStr(const string & value, const string & name) = 0;
    virtual void addArrInt(const vector<int> & vec, const string & name) = 0;
    virtual void addArrStr(const vector<string> & vec, const string & name) = 0;
    virtual void clear() = 0;
    virtual string getRes() = 0;
    virtual void setJson(const string & jsonData) = 0;
    virtual bool getBool(const string & name) = 0;
    virtual int getInt(const string & name) = 0;
    virtual string getStr(const string & name) = 0;
    virtual vector<int> getArrInt(const string & name) = 0;
    virtual vector<string> getArrStr(const string & name) = 0;
    virtual void addChild(const string & json, const string & name) = 0;
    virtual void addArrChild(const vector<string> & jsons, const string & name) = 0;
    virtual string getChild(const string & name) = 0;
    virtual vector<string> getArrChild(const string & name) = 0;
};

class Parser: public AbstractParser {
private:
    bptree::ptree root;
public:
    Parser(): root() {}
    void addBool(const bool & value, const string & name) override;
    void addInt(const int & value, const string & name) override;
    void addStr(const string & value, const string & name) override;
    void addArrInt(const vector<int> & vec, const string & name) override;
    void addArrStr(const vector<string> & vec, const string & name) override;
    void clear() override;
    string getRes() override;
    void setJson(const string & jsonData) override;
    bool getBool(const string & name) override;
    int getInt(const string & name) override;
    string getStr(const string & name) override;
    vector<int> getArrInt(const string & name) override;
    vector<string> getArrStr(const string & name) override;
    void addChild(const string & json, const string & name) override;
    void addArrChild(const vector<string> & jsons, const string & name) override;
    string getChild(const string & name) override;
    vector<string> getArrChild(const string & name) override;
};


#endif //NETLIB_PARSER_H
