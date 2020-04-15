#include "DBWorker.h"

DBWorker::DBWorker() {
    DBInstanceSingleton::inctance();
}

void DBWorker::SetNeededFile(std::string filepath) {

}

int DBWorker::GetInt(std::string key) {
    return 0;
}

std::vector<std::string> DBWorker::GetStrVec(std::string key) {
    return std::vector<std::string>();
}

std::string DBWorker::GetStr(std::string key) {
    return std::__cxx11::string();
}

std::map<std::string, std::string> DBWorker::GetMap(std::string key) {
    return std::map<std::string, std::string>();
}

std::string DBWorker::CreateFile(std::string col) {
    return std::__cxx11::string();
}

void DBWorker::AddInt(std::string key, int val) {

}

void DBWorker::AddStr(std::string key, std::string val) {

}

void DBWorker::AddStrVec(std::string key, std::vector<std::string> val) {

}

void DBWorker::AddMap(std::string key, std::map<std::string, std::string> val) {

}

DBWorker::~DBWorker() {

}
