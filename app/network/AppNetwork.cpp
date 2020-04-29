#include "AppNetwork.h"


AppNetwork::AppNetwork() {

}

AppNetwork::~AppNetwork() {

}

shared_ptr<AppNetwork> AppNetwork::shared() {
    return unique_ptr<AppNetwork>();
}

void AppNetwork::login(const string &name, const string &password, const function<void(const MyAccount &)> &callback) {

}

void AppNetwork::registration(const MyAccount &acc, const function<void(const int &)> &callback) {

}

void AppNetwork::getListChat(const int &idUser, const function<void(const vector<ChatInfo> &)> &callback) {

}

void AppNetwork::getChatRoom(const int &idChat, const function<void(const ChatRoom &)> &callback) {

}

void AppNetwork::setObserverChat(const int &idChat, const function<void(const ChatChange &)> &callback) {

}

void AppNetwork::sendMessage(const Message &msg, const function<void(const bool &)> &callback) {

}

void AppNetwork::getUser(const int &id, const function<void(const UserInfo &)> &callback) {

}

void AppNetwork::saveMyAvatar(const string &path, const function<void(const string &)> &callback) {

}

void AppNetwork::getMessages(const int &start, const int &begin, const int &amount,
                             const function<void(vector<Message> &)> &callback) {

}

void AppNetwork::addChat(ChatRoom &room, const function<void(const ChatRoom &)> &callback) {

}

bool AppNetwork::check() {
    return false;
}

optional<MyAccount> AppNetwork::getMe() {
    return nullopt;
}
