//
// Created by Sergei Alexeev on 05.05.2020.
//

#include "Parser.h"
#include <boost/algorithm/string.hpp>

using namespace std;
namespace bptree = boost::property_tree;

void Parser::addBool(bool value, const string &name) {
    root.put(name, value);
}

void Parser::addInt(int value, const string &name) {
    root.put(name, value);
}

void Parser::addStr(const string &value, const string &name) {
    root.put(name, value);
}

void Parser::addArrInt(const vector<int> &vec, const string &name) {
    bptree::ptree tmp;
    if(vec.empty()) {
        tmp.put("", "[]");
    }
    for(const auto & item: vec) {
        bptree::ptree element;
        element.put("", item);
        tmp.push_back(make_pair("", element));
    }
    root.add_child(name, tmp);
}

void Parser::addArrStr(const vector<string> &vec, const string &name) {
    bptree::ptree tmp;
    if(vec.empty()) {
        tmp.put("", "[]");
    }
    for(const auto & item: vec) {
        bptree::ptree element;
        element.put("", item);
        tmp.push_back(make_pair("", element));
    }
    root.add_child(name, tmp);
}

void Parser::clear() {
    root.clear();
}

string Parser::getRes() {
    stringstream result;
    bptree::write_json(result, root);
    string resStr = result.str();
    boost::replace_all(resStr, "\"[]\"", "[]");
    return resStr;
}

void Parser::setJson(const string &jsonData) {
    clear();
    std::stringstream jsonEncodedData(jsonData);
    bptree::read_json(jsonEncodedData, root);
}

bool Parser::getBool(const string &name) {
    return root.get<bool>(name);
}

int Parser::getInt(const string &name) {
    return root.get<int>(name);
}

string Parser::getStr(const string &name) {
    return root.get<string>(name);
}

vector<int> Parser::getArrInt(const string &name) {
    vector<int> res;
    for(const auto & item: root.get_child(name)) {
        auto tmp = item.second.get_value_optional<int>();
        if(tmp) {
            res.push_back(tmp.value());
        }
    }
    return res;
}

vector<string> Parser::getArrStr(const string &name) {
    vector<string> res;
    for(const auto & item: root.get_child(name)) {
        res.push_back(item.second.get_value<string>());
    }
    return res;
}

void Parser::addCustom(const string &json, const string &name) {
    bptree::ptree tmp;
    stringstream ss(json);
    bptree::read_json(ss, tmp);
    root.add_child(name, tmp);
}

void Parser::addArrCustom(const vector<string> &jsons, const string &name) {
    bptree::ptree tmp;
    if(jsons.empty()) {
        tmp.put("", "[]");
    }
    for(const auto & item: jsons) {
        bptree::ptree elem;
        stringstream ss(item);
        bptree::read_json(ss, elem);
        tmp.push_back(make_pair("", elem));
    }
    root.add_child(name, tmp);
}

string Parser::getCustom(const string &name) {
    stringstream ss;
    bptree::write_json(ss, root.get_child(name));
    return ss.str();
}

vector<string> Parser::getArrCustom(const string &name) {
    vector<string> res;
    for(const auto & item : root.get_child(name)) {
        stringstream ss;
        bptree::write_json(ss, item.second);
        res.push_back(ss.str());
    }
    return res;
}





