#include "DBWorker.h"

DBWorker::DBWorker(const std::string &collectionName) {
    try {
        DBInstanceSingleton::inctance();
        client = mongocxx::client{mongocxx::uri{}};
        collection = client[dbName][collectionName];
    }
    catch (mongocxx::exception &mongoEx) {
        std::cout << "You must start mongoDB before starting server" << std::endl;
        exit(-1);
    }
    doc[1] << "$set" << open_document;
}

int DBWorker::GetInt(const std::string& key) {
    auto iter = res.find(key);
    if (!*iter){
        error += "Such " + key + " doesn't exist; ";
        return 0;
    }
    return iter->get_int32();
}

std::vector<std::string> DBWorker::GetStrVec(const std::string& key) {
    std::vector<std::string> v;
    auto iter = res.find(key);
    if (!*iter) {
        error += "Such " + key + " doesn't exist; ";
        return v;
    }

    for (auto&& i : iter->get_array().value){
        v.push_back(i.get_utf8().value.to_string());/// здесь нельзя применить метод toString, т.к. переменная i
        /// имеет тип array::element, а не document::element
    }

    return v;
}

std::string DBWorker::GetStr(const std::string &key) {
    auto iter = res.find(key);
    if (!*iter) {
        error += "Such " + key + " doesn't exist; ";
        return {};
    }
    return toString(*iter);
}

bool DBWorker::GetBool(const std::string &key) {
    auto iter = res.find(key);
    if (!*iter) {
        error += "Such " + key + " doesn't exist; ";
        return false;
    }
    return iter->get_bool();
}

std::map<std::string, std::string> DBWorker::GetMap(const std::string &key) {
    std::map<std::string, std::string> m;
    auto iter = res.find(key);
    if (!*iter) {
        error += "Such " + key + " doesn't exist; ";
        return m;
    }

    for (auto &&i : iter->get_document().value) {
        m[i.key().to_string()] = toString(i);
    }

    return m;
}

void DBWorker::AddInt(const std::string &key, int data, bool flag) {
    doc[flag] << key << data;
}

void DBWorker::AddBool(const std::string &key, bool data, bool flag) {
    doc[flag] << key << data;
}

void DBWorker::AddStr(const std::string &key, const std::string &data, bool flag) {
    doc[flag] << key << data;
}

void DBWorker::AddStrVec(const std::string &key, const std::vector<std::string> &data, bool flag) {
    auto arr = doc[flag] << key << open_array;
    for (auto &&i : data) {
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

int DBWorker::UpdateDoc(const std::string &collect) {
    auto c = client[dbName][collect];
    bsoncxx::document::view_or_value filter = doc[0] << finalize;
    doc[1] << close_document;
    bsoncxx::document::view_or_value update = doc[1] << finalize;
    auto maybeUpdated = c.update_one(filter, update);
    doc[0].clear();
    doc[1].clear();
    doc[1] << "$set" << open_document;
    return maybeUpdated->modified_count();
}

int DBWorker::DeleteDoc(const std::string &collect) {
    auto c = client[dbName][collect];
    bsoncxx::document::view_or_value filter = doc[0] << finalize;
    auto maybeDeleted = c.delete_one(filter);
    doc[0].clear();
    return maybeDeleted->deleted_count();
}

void DBWorker::DeleteCollect(const std::string& collect){
    auto c = client[dbName][collect];
    c.drop();
}

void DBWorker::SaveDoc(bool flag) {
    auto val = doc[flag] << finalize;
    collection.insert_one(val.view());
    doc[flag].clear();
}

bool DBWorker::FindInt(const std::string &key, int lBoard, int rBoard) {
    if (rBoard < lBoard)
        rBoard = lBoard;
    cur.reset();
    cur = collection.find({bsoncxx::builder::stream::document{} << key << open_document << "$gte" << lBoard
                                                                << "$lte" << rBoard << close_document << finalize});

    if (cur->begin() != cur->end()) {
        res = *cur.value().begin();
        return true;
    }

    return false;
}

bool DBWorker::FindBool(const std::string &key, bool val) {
    cur.reset();
    cur = collection.find({bsoncxx::builder::stream::document{} << key << val << finalize});

    if (cur->begin() != cur->end()) {
        res = *cur.value().begin();
        return true;
    }

    return false;
}

bool DBWorker::FindStr(const std::string &key, const std::string &data) {
    cur.reset();
    cur = collection.find({bsoncxx::builder::stream::document{} << key << open_document << "$gte" << data
                                                                << "$lte" << data << close_document << finalize});

    if (cur->begin() != cur->end()) {
        res = *cur.value().begin();
        return true;
    }

    return false;
}

void DBWorker::ChangeCollection(const std::string &collectionName){
    collection = client[dbName][collectionName];
}


bool DBWorker::NextDoc(){
    auto it = cur.value().begin();
    it++;
    res = *it;
    return cur.value().end() != it;
}

void DBWorker::Clear() {
    doc[0].clear();
    doc[1].clear();
    doc[1] << "$set" << open_document;
    cur.reset();
    error.clear();
}

std::vector<int> DBWorker::GetIntVec(const std::string &key) {
    std::vector<int> v;
    auto iter = res.find(key);
    if (!*iter) {
        error += "Such " + key + " doesn't exist; ";
        return v;
    }

    for (auto&& i : iter->get_array().value){
        v.push_back(i.get_int32());
    }

    return v;
}

void DBWorker::AddIntVec(const std::string &key, const std::vector<int>& data, bool flag) {
    auto arr = doc[flag] << key << open_array;
    for (auto&& i : data){
        arr << i;
    }
    arr << close_array;
}

DBWorker::DBWorker() {
    try {
        DBInstanceSingleton::inctance();
        client = mongocxx::client{mongocxx::uri{}};
        collection = client[dbName]["Info"];
    }
    catch(mongocxx::exception& mongoEx) {
        std::cout << "You must start mongoDB before starting server" << std::endl;
        exit(-1);
    }
    doc[1] << "$set" << open_document;
}

std::string DBWorker::toString(bsoncxx::v_noabi::document::element elem) {
    return elem.get_utf8().value.to_string();
}

std::string DBWorker::GetErrors() {
    return error;
}

std::string DBWorker::GetJson() {
    return bsoncxx::to_json(res);
}
