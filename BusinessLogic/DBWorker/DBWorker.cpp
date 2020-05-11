#include "DBWorker.h"

DBWorker::DBWorker() {
    DBInstanceSingleton::inctance();
}

void DBWorker::SetNeededFile(const std::string& filepath) {

}

int DBWorker::GetInt(const std::string& key) {
    return 0;
}

std::vector<std::string> DBWorker::GetStrVec(const std::string& key) {
    return std::vector<std::string>();
}

std::string DBWorker::GetStr(const std::string& key) {
    return std::__cxx11::string();
}

std::map<std::string, std::string> DBWorker::GetMap(const std::string& key) {
    return std::map<std::string, std::string>();
}

std::string DBWorker::CreateFile(const std::string& col) {
    return std::__cxx11::string();
}

void DBWorker::AddInt(const std::string& key, int val) {

}

void DBWorker::AddStr(const std::string& key, const std::string& val) {

}

void DBWorker::AddStrVec(const std::string& key, const std::vector<std::string>& val) {

}

void DBWorker::AddMap(const std::string& key, const std::map<std::string, std::string>& val) {

}

DBWorker::~DBWorker() {

}
