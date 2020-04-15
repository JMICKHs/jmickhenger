//
// Created by Sergei Alexeev on 13.04.2020.
//

#include "Cache.h"


bool Cache::save(Info::MyAccount acc) {
    return false;
}

bool Cache::save(Info::UserInfo user) {
    return false;
}

bool Cache::save(vector<Info::ChatInfo> chatList) {
    return false;
}

Info::MyAccount *Cache::getMyAccount() {
    return nullptr;
}

Info::UserInfo *Cache::getUser(int idUser) {
    return nullptr;
}

vector<Info::ChatInfo> Cache::getChatList() {
    return vector<Info::ChatInfo>();
}
