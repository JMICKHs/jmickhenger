#include "JsonParser.h"

JsonParser::JsonParser() {
    c = 0;
}

void JsonParser::SetJson (const std::string& json){
    st.clear();
    std::stringstream ss(json);
    st.emplace_back(boost::property_tree::ptree());
    boost::property_tree::read_json(ss, st.front());
    c = 1;
    q.clear();
}

void JsonParser::ParseDict(const std::string& key){
    boost::property_tree::ptree tmp;
    tmp = st.front().get_child(key);
    st.emplace_front(tmp);
    q.push_back(c);
    c++;
}

void JsonParser::MemorizePos(){
    q.emplace_back(c);
}

void JsonParser::ForgotPos(){
    q.pop_back();
}

void JsonParser::JumpToPos(){
    unsigned int tmp = q.back();
    q.pop_back();
    while(tmp != c){
        st.pop_front();
        --c;
    }
}


std::vector<int> JsonParser::GetIntVec(){
    std::vector<int> vec;
    for (auto&& i : st.front()){
        vec.push_back(i.second.get_value<int>());
    }
    return vec;
}

std::vector<std::string> JsonParser::GetStrVec(){
    std::vector<std::string> vec;
    for (auto&& i : st.front()){
        vec.push_back(i.second.get_value<std::string>());
    }
    return vec;
}

std::map<std::string, int> JsonParser::GetIntMap(){
    std::map<std::string, int> m;
    for (auto&& i : st.front()){
        m[i.first] = i.second.get_value<int>();
    }
    return m;
}

std::map<std::string, std::string> JsonParser::GetStrMap(){
    std::map<std::string, std::string> m;
    for (auto&& i : st.front()){
        m[i.first] = i.second.get_value<std::string>();
    }
    return m;
}

void JsonParser::ParseVec(){
    auto tmp = st.front();
    for (auto i = tmp.rbegin(); i != tmp.rend(); i++){
        st.push_front(i->second);
        ++c;
        q.push_back(c);
    }
    q.pop_back();
}

int JsonParser::GetInt(const std::string& key){
    return st.front().get<int>(key);
}

std::string JsonParser::GetStr(const std::string& key){
    return st.front().get<std::string>(key);
}

void JsonParser::CreateDict(const std::string& key){
    st.emplace_front(boost::property_tree::ptree());
    qs.push_front(key);
    c++;
}

void JsonParser::AddInt(int val){
    st.front().put_value(val);
}

void JsonParser::AddVec(const std::string& key, const std::vector<int>& vec){
    for (auto&& i : vec){
        boost::property_tree::ptree p;
        p.put_value(i);
        st.push_front(p);
        qs.push_front("");
        c++;
    }
    BuildList(key);
}

void JsonParser::AddMap(const std::string& key, const std::map<std::string, int>& m){
    for (auto&& i : m){
        boost::property_tree::ptree p;
        p.put_value(i.second);
        st.push_front(p);
        qs.push_front(i.first);
        c++;
    }
    BuildList(key);
}

void JsonParser::AddPairInt(const std::string& key, int val){
    st.front().put(key, val);
}

void JsonParser::AddStr(const std::string& val){
    st.front().put_value(val);
}

void JsonParser::AddPairStr(const std::string& key, const std::string& val){
    st.front().put(key, val);
}

void JsonParser::BuildList(const std::string& key){
    boost::property_tree::ptree pt;
    int startPos = q.empty() ? 0 : q.back();
    for (int i = st.size(); i > startPos; --i){
        pt.push_front(std::make_pair(qs.front(), st.front()));
        qs.pop_front();
        st.pop_front();
    }
    st.push_front(pt);
    qs.push_front(key);
    c = st.size();
}

void JsonParser::BuildAll(const std::string& key){
    q.clear();
    BuildList(key);
}

std::string JsonParser::GetJson(){
    std::stringstream ss;
    boost::property_tree::write_json(ss, st.front());
    st.clear();
    qs.clear();
    c = 0;
    q.clear();
    return ss.str();
}

void JsonParser::Reverse(){
    std::reverse(st.begin(), st.end());
    std::reverse(qs.begin(), qs.end());
}