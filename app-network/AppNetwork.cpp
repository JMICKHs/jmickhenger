//
// Created by Sergei Alexeev on 11.04.2020.
//

#include "AppNetwork.h"

AppNetwork::AppNetwork() : client(), announcer() {
    client.start();
}

AppNetwork * AppNetwork::shared() {
//    if (AppNetwork::singleton == nullptr) {
//        //lock
//        if (singleton == nullptr) {
//            AppNetwork::singleton = new AppNetwork;
//        }
//    }
//
//    return singleton;
    return nullptr;
}

AppNetwork::~AppNetwork() {

}

void AppNetwork::login(string name, string password, const function<void(const MyAccount)>& callback) {
    //логика связаная с сервером
    MyAccount acc;
    callback(acc);
}

void AppNetwork::registration(MyAccount acc, const function<void(const int)> &callback) {
    //логика связаная с сервером
    int id = 1023;
    callback(id);
}

void AppNetwork::getListChat(unsigned int idUser, const function<void(const vector<ChatInfo>)> &callback) {
    //логика связаная с сервером
    vector<ChatInfo> arr;
    callback(arr);
}

void AppNetwork::getChatRoom(unsigned int idChat, const function<void(const ChatRoom)> &callback) {
    //логика связаная с сервером
    ChatRoom room;
    callback(room);
}

void AppNetwork::setObserverChat(unsigned int idChat, const function<void(const ChatChange)> &callback) {
    //логика связаная с announcer
    //сохранить callback
}

void AppNetwork::sendMessage(Message msg, const function<void(const bool)> &callback) {

}

void AppNetwork::getUser(unsigned int id, const function<void(const UserInfo)> &callback) {

}

void AppNetwork::getMyAccount(MyAccount acc, const function<void(const MyAccount)> &callback) {

}

void AppNetwork::saveAvatar(string path, const function<void(const bool)> &callback) {

}

bool AppNetwork::check() {
    return false;
}



