//
// Created by Sergei Alexeev on 05.05.2020.
//

#include "Cache.h"

using namespace std;

Cache::Cache() {

}

bool Cache::save(inf::MyAccount &acc) {
    return false;
}

bool Cache::save(inf::UserInfo &user) {
    return false;
}

bool Cache::save(vector<inf::ChatInfo> &chatList) {
    return false;
}

std::optional<inf::MyAccount> Cache::getMyAccount() {
    return nullopt;
}

std::optional<inf::UserInfo> Cache::getUser(int idUser) {
    return nullopt;
}

vector<inf::ChatInfo> Cache::getChatList() {
    return vector<inf::ChatInfo>();
}


