#include "AppNetwork.h"

AppNetwork::AppNetwork() {
    //client.start();
}

AppNetwork * AppNetwork::shared() {
//    if (AppNetwork::singleton == nullptr) {
//        //lock
//        if (singleton == nullptr) {
//            AppNetwork::singleton = new AppNetwork;
//        }
//    }
//    singleton.clientDelegate = delegate;
//    return singleton;
    return nullptr;
}

AppNetwork::~AppNetwork() {

}

void AppNetwork::login(string name, string password, const function<void(const Info::MyAccount)>& callback) {
    //логика связаная с сервером
    Info::MyAccount acc;
    callback(acc);
}

void AppNetwork::registration(Info::MyAccount acc, const function<void(const int)> &callback) {
    //логика связаная с сервером
    int id = 1023;
    callback(id);
}

void AppNetwork::getListChat(unsigned int idUser, const function<void(const vector<Info::ChatInfo>)> &callback) {
    //логика связаная с сервером
    vector<Info::ChatInfo> arr;
    callback(arr);
}

void AppNetwork::getChatRoom(unsigned int idChat, const function<void(const Info::ChatRoom)> &callback) {
    //логика связаная с сервером
    Info::ChatRoom room;
    callback(room);
}

void AppNetwork::setObserverChat(unsigned int idChat, const function<void(const Info::ChatChange)> &callback) {
    //логика связаная с announcer
    //сохранить callback
}

void AppNetwork::sendMessage(Info::Message msg, const function<void(const bool)> &callback) {

}

void AppNetwork::getUser(unsigned int id, const function<void(const Info::UserInfo)> &callback) {

}


void AppNetwork::saveAvatar(string path, const function<void(const bool)> &callback) {

}

bool AppNetwork::check() {
    return false;
}
