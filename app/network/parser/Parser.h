//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_PARSER_H
#define NETWORK_PARSER_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>

using namespace std;
namespace bptree = boost::property_tree;

class Parser {
private:
    bptree::ptree root;
public:
    Parser(): root() {}
    void addBool(const bool & value, const string & name) {
        root.put(name, value);
    }
    void addInt(const int & value, const string & name) {
        root.put(name, value);
    }
    void addStr(const string & value, const string & name) {
        root.put(name, value);
    }
    void addArrInt(const vector<int> & vec, const string & name) {
        bptree::ptree tmp;
        for(const auto & item: vec) {
            bptree::ptree element;
            element.put("", item);
            tmp.push_back(make_pair("", element));
        }
        root.add_child(name, tmp);
    }
    void addArrStr(const vector<string> & vec, const string & name) {
        bptree::ptree tmp;
        for(const auto & item: vec) {
            bptree::ptree element;
            element.put("", item);
            tmp.push_back(make_pair("", element));
        }
        root.add_child(name, tmp);
    }
    void clear() {
        root.clear();
    }
    string getRes() {
        std::stringstream result;
        boost::property_tree::write_json(result, root);
        return result.str();
    }
    void setJson(const string & jsonData) {
        clear();
        std::stringstream jsonEncodedData(jsonData);
        boost::property_tree::read_json(jsonEncodedData, root);
    }
    bool getBool(const string & name) {
        return root.get<bool>(name);
    }
    int getInt(const string & name) {
        return root.get<int>(name);
    }
    string getStr(const string & name) {
        return root.get<string>(name);
    }
    vector<int> getArrInt(const string & name) {
        vector<int> res;
        for(const auto & item: root.get_child(name)) {
            res.push_back(item.second.get_value<int>());
        }
        return res;
    }
    vector<string> getArrStr(const string & name) {
        vector<string> res;
        for(const auto & item: root.get_child(name)) {
            res.push_back(item.second.get_value<string>());
        }
        return res;
    }
};


#endif //NETWORK_PARSER_H
