#include "JsonParser.h"

JsonParser::JsonParser() {
    cntr = 0;
}

void JsonParser::SetJson (const std::string& json) {
    docsStack.clear();
    std::stringstream ss(json);
    docsStack.emplace_back(boost::property_tree::ptree());
    boost::property_tree::read_json(ss, docsStack.front());
    cntr = 1;
    posQueue.clear();
}

void JsonParser::ParseDict(const std::string& key) {
    boost::property_tree::ptree tmp;
    tmp = docsStack.front().get_child(key);
    docsStack.emplace_front(tmp);
    posQueue.push_back(cntr);
    cntr++;
}

void JsonParser::MemorizePos(){
    posQueue.emplace_back(cntr);
}

void JsonParser::ForgotPos(int n) {
    for (int i = 0; i < n; ++i)
        posQueue.pop_back();
}

void JsonParser::JumpToPos() {
    unsigned int tmp = posQueue.back();
    posQueue.pop_back();
    while (tmp != cntr) {
        docsStack.pop_front();
        --cntr;
    }
}


std::vector<int> JsonParser::GetIntVec(){
    std::vector<int> vec;
    for (auto &&i : docsStack.front()) {
        vec.push_back(i.second.get_value<int>());
    }
    return vec;
}

std::vector<std::string> JsonParser::GetStrVec(){
    std::vector<std::string> vec;
    for (auto &&i : docsStack.front()) {
        vec.push_back(i.second.get_value<std::string>());
    }
    return vec;
}

std::map<std::string, int> JsonParser::GetIntMap(){
    std::map<std::string, int> m;
    for (auto &&i : docsStack.front()) {
        m[i.first] = i.second.get_value<int>();
    }
    return m;
}

std::map<std::string, std::string> JsonParser::GetStrMap(){
    std::map<std::string, std::string> m;
    for (auto &&i : docsStack.front()) {
        m[i.first] = i.second.get_value<std::string>();
    }
    return m;
}

void JsonParser::ParseVec(){
    auto tmp = docsStack.front();
    for (auto i = tmp.rbegin(); i != tmp.rend(); i++) {
        docsStack.push_front(i->second);
        ++cntr;
        posQueue.push_back(cntr);
    }
    posQueue.pop_back();
}

int JsonParser::GetInt(const std::string& key){
    return docsStack.front().get<int>(key);
}

std::string JsonParser::GetStr(const std::string& key){
    return docsStack.front().get<std::string>(key);
}

void JsonParser::CreateDict(const std::string& key) {
    docsStack.emplace_front(boost::property_tree::ptree());
    namesQueue.push_front(key);
    cntr++;
}

void JsonParser::AddInt(int val){
    docsStack.front().put_value(val);
}

void JsonParser::AddVec(const std::string& key, const std::vector<int>& vec){
    for (auto&& i : vec) {
        boost::property_tree::ptree p;
        p.put_value(i);
        docsStack.push_front(p);
        namesQueue.push_front("");
        cntr++;
    }
    if (vec.empty()) {
        docsStack.emplace_front(boost::property_tree::ptree{});
        namesQueue.push_front("");
    }
    BuildList(key);
}

void JsonParser::AddMap(const std::string& key, const std::map<std::string, int>& m){
    for (auto&& i : m) {
        boost::property_tree::ptree p;
        p.put_value(i.second);
        docsStack.push_front(p);
        namesQueue.push_front(i.first);
        cntr++;
    }
    BuildList(key);
}

void JsonParser::AddPairInt(const std::string& key, int val){
    CreateDict(key);
    AddInt(val);
}

void JsonParser::AddStr(const std::string& val){
    docsStack.front().put_value(val);
}

void JsonParser::AddPairStr(const std::string& key, const std::string& val){
    CreateDict(key);
    AddStr(val);
}

void JsonParser::BuildList(const std::string& key) {
    boost::property_tree::ptree pt;
    int startPos = posQueue.empty() ? 0 : posQueue.back();
    for (int i = docsStack.size(); i > startPos; --i) {
        pt.push_front(std::make_pair(namesQueue.front(), docsStack.front()));
        namesQueue.pop_front();
        docsStack.pop_front();
    }
    docsStack.push_front(pt);
    namesQueue.push_front(key);
    cntr = docsStack.size();
}

void JsonParser::BuildAll(const std::string& key){
    posQueue.clear();
    BuildList(key);
}

std::string JsonParser::GetJson() {
    std::stringstream ss;
    boost::property_tree::write_json(ss, docsStack.front());
    docsStack.clear();
    namesQueue.clear();
    cntr = 0;
    posQueue.clear();
    std::string str = ss.str();
    CompressStr(str);
    return str;
}

void JsonParser::Reverse() {
    std::reverse(docsStack.begin(), docsStack.end());
    std::reverse(namesQueue.begin(), namesQueue.end());
}

void JsonParser::Clear() {
    cntr = 0;
    docsStack.clear();
    posQueue.clear();
    namesQueue.clear();
}

void JsonParser::CompressStr(std::string &JsonStr) {
    bool wasSlash = false;
    JsonStr.erase(std::remove_if(JsonStr.begin(), JsonStr.end(), [&wasSlash](char c) {
        if (c == '\"')
            wasSlash = !wasSlash;
        return (c == ' ' && !wasSlash) || c == '\n';
    }), JsonStr.end());
}

int JsonParser::GetBool(const std::string &key) {
    return docsStack.front().get<bool>(key);
}

void JsonParser::AddBool(bool val) {
    docsStack.front().put_value(val);
}

void JsonParser::AddPairBool(const std::string &key, bool val) {
    CreateDict(key);
    AddBool(val);
}
