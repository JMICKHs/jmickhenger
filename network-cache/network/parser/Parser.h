//
// Created by Sergei Alexeev on 13.04.2020.
//

#ifndef NETWORK_CACHE_PARSER_H
#define NETWORK_CACHE_PARSER_H

#include <string>
#include <vector>
#include "../info/Info.h"

using namespace std;

class Parser {
private:
    // boost::property_tree::ptree
public:
    string json;
    void createJson() {}
    void setJson(string body) {}
    void setInt(int n, string name) {}
    void setString(string n, string name) {}
    void setDate(string n, string name) {}
    void setBool(bool b, string name) {}
    void setMatrixInt(vector<int> n, string name) {}
    void setMatrixMessage(vector<Info::Message> n, string name) {}
    int getInt(string name) {}
    string getString(string name) {}
    int getDate(string name) {}
    bool getBool(string name) {}
    vector<int> setMatrixInt(string name) {}
    vector<Info::Message> setMatrixMessage(string name) {}
};


#endif //NETWORK_CACHE_PARSER_H
