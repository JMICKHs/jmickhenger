#include "DBWorker.h"

DBWorker::DBWorker(const std::string &collectionName) {
    DBInstanceSingleton::inctance();
    client = mongocxx::client{mongocxx::uri{}};
    collection = client[dbName][collectionName];
    doc[1] << "$set" << open_document;
}

int DBWorker::GetInt(const std::string& key) {
    return res.find(key)->get_int32();
}

std::vector<std::string> DBWorker::GetStrVec(const std::string& key) {
    std::vector<std::string> v;

    for (auto&& i : res.find(key)->get_array().value){
        v.push_back(i.get_utf8().value.to_string());
    }

    return v;
}

std::string DBWorker::GetStr(const std::string& key) {
    return res.find(key)->get_utf8().value.to_string();
}

std::map<std::string, std::string> DBWorker::GetMap(const std::string& key) {
    std::map<std::string, std::string> m;

    for (auto&& i : res.find(key)->get_document().value){
        m[i.key().to_string()] = i.get_utf8().value.to_string();
    }

    return m;
}

void DBWorker::AddInt(const std::string& key, int data, bool flag) {
    doc[flag] << key << data;
}

void DBWorker::AddStr(const std::string& key, const std::string& data, bool flag) {
    doc[flag] << key << data;
}

void DBWorker::AddStrVec(const std::string& key, const std::vector<std::string>& data, bool flag) {
    auto arr = doc[flag] << key << open_array;
    for (auto&& i : data){
        arr << i;
    }
    arr << close_array;
}

void DBWorker::AddMap(const std::string& key, const std::map<std::string, std::string>& data, bool flag) {
    doc[flag] << key << open_document;
    for (auto&& i : data){
        doc[flag] << i.first << i.second;
    }
    doc[flag] << close_document;
}

void DBWorker::UpdateDoc(const std::string& collect){
    mongocxx::client tmpClient{mongocxx::uri{}};////////////////////////////////??????????????????????????????????????????????????????
    auto c = tmpClient[dbName][collect];
    bsoncxx::document::view_or_value filter = doc[0] << finalize;
    doc[1] << close_document;
    bsoncxx::document::view_or_value update = doc[1] << finalize;
    c.update_one(filter, update);
    doc[0].clear();
    doc[1].clear();
    doc[1] << "$set" << open_document;
}

void DBWorker::DeleteDoc(const std::string& collect){
    mongocxx::client tmpClient{mongocxx::uri{}};////////////////////////////////??????????????????????????????????????????????????????
    auto c = tmpClient[dbName][collect];
    bsoncxx::document::view_or_value filter = doc[0] << finalize;
    c.delete_one(filter);
    doc[0].clear();
}

void DBWorker::DeleteCollect(const std::string& collect){
    mongocxx::client tmpClient{mongocxx::uri{}};////////////////////////////////??????????????????????????????????????????????????????
    auto c = tmpClient[dbName][collect];
    c.drop();
}

void DBWorker::SaveDoc(bool flag) {
    auto val = doc[flag] << finalize;
    collection.insert_one(val.view());
    doc[flag].clear();
}

void DBWorker::Find(const std::string &key, int lBoard, int rBoard) {
    if (rBoard < lBoard)
        rBoard = lBoard;
    cur.reset();
    cur = collection.find({bsoncxx::builder::stream::document{} << key << open_document << "$gte" << lBoard
                                                                << "$lte" << rBoard << close_document << finalize});

    res = *cur.value().begin();
}

void DBWorker::NextDoc(){
    auto it = cur.value().begin();
    it++;
    res = *it;
}