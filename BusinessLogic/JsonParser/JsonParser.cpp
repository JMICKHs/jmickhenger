#include "JsonParser.h"

JsonParser::JsonParser() = default;

std::string JsonParser::CreateJson() {
    return std::__cxx11::string();
}

void JsonParser::AddInt(const std::string& key, int val) {

}

void JsonParser::AddStr(const std::string& key, const std::string& val) {

}

void JsonParser::AddStrVec(const std::string& key, const std::vector<std::string>& val) {

}

void JsonParser::AddMap(const std::string& key, const std::map<std::string, std::string>& val) {

}

void JsonParser::SetNeededFile(const std::string& str) {

}

int JsonParser::GetInt(const std::string& key) {
    return 0;
}

std::string JsonParser::GetStr(const std::string& key) {
    return std::__cxx11::string();
}

std::vector<std::string> JsonParser::GetStrVec(const std::string& key) {
    return std::vector<std::string>();
}

std::map<std::string, std::string> JsonParser::GetMap(const std::string& key) {
    return std::map<std::string, std::string>();
}