//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_APPNETWORK_H
#define NETLIB_APPNETWORK_H


#include "announcer/Announcer.h"
#include "client/Client.h"
#include "cache/Cache.h"
#include "info/Info.h"
#include <string>
#include <functional>
#include <vector>
#include <optional>
#include <memory>

using namespace std;
using namespace inf;


// cmd
// 1 - регистрация
// 2 - авторизация
// 3 - получить список чатов
// 4 - получить чат
// 5 - отправить сообщения
// 6 - получить определенные сообщения
// 7 - входящие сообщения
// 8 - получить последнее сообщение
// 9 - добавить в друзья
// 10 - получить список друзей
// 11 - получить информацию о себе
// 12 - получить информацию о другом пользователе
// 13 - создать чат
// 14 - получить последнее сообщение
// 15 - сохранить аватарку
// 16 - изменение логина
// 17 - изменение пароля
// 18 - удаление сообщения в чате

using errstr = optional<string>;

class AppNet: enable_shared_from_this<AppNet> {
public:
private:
    AppNet();
    static optional<shared_ptr<AppNet>> single;
    unique_ptr<Announcer> announcer;
    unique_ptr<AbstractCache> cache;
    shared_ptr<AbstractClient> client;
};

class AbstractNetwork {
public:
    virtual optional<MyAccount> getMe() = 0;
    virtual void login(const string & name, const string & password, const function<void(const MyAccount &, optional<string> &)> & callback) = 0;
    virtual void registration(const MyAccount & acc, const function<void(const int &, optional<string> &)>& callback) = 0; //если id == 0, то неудачно
    virtual void getListChat(const int & idUser, const function<void(const vector<ChatInfo> &)> & callback) = 0;
    virtual void getChatRoom(const int & idChat, const function<void(const ChatRoom &)> & callback) = 0;
    virtual void setObserverChat(const int & idChat, const function<void(const ChatChange &)>& callback) = 0;
    virtual void setObserverAnonChat(const function<void(const ChatChange &)>& callback) = 0;
    virtual void sendMessage(const Message & msg, const function<void(const bool &, optional<string> &)> & callback) = 0; // отправилось или нет bool
    virtual void getUser(const int & id, const function<void(const UserInfo &)> & callback) = 0;
    virtual void saveMyAvatar(const string &path, const function<void(const string &, optional<string> &)> & callback) = 0;
    virtual void getMessages(const int & start, const int & begin, const int & idChat, const function<void(vector<Message> &)> & callback) = 0;
    virtual void addChat(ChatRoom & room, const function<void(const ChatRoom &, optional<string> &)> & callback) = 0;
    virtual bool check() = 0;
};

class AppNetwork : AbstractNetwork {
public:
    AppNetwork(const AppNetwork &other) = delete;
    AppNetwork(AppNetwork &&other) = delete;
    static shared_ptr<AppNetwork> shared();
    optional<MyAccount> getMe() {}
    void login(const string & name, const string & password, const function<void(const MyAccount &, optional<string> &)> & callback) {}
    void registration(const MyAccount & acc, const function<void(const int &, optional<string> &)>& callback) {} //если id == 0, то неудачно
    void getListChat(const int & idUser, const function<void(const vector<ChatInfo> &)> & callback) {}
    void getChatRoom(const int & idChat, const function<void(const ChatRoom &)> & callback) {}
    void setObserverChat(const int & idChat, const function<void(const ChatChange &)>& callback) {}
    void setObserverAnonChat(const function<void(const ChatChange &)>& callback) {}
    void sendMessage(const Message & msg, const function<void(const bool &, optional<string> &)> & callback) override; // отправилось или нет bool
    void getUser(const int & id, const function<void(const UserInfo &)> & callback) {}
    void saveMyAvatar(const string &path, const function<void(const string &, optional<string> &)> & callback) {}
    void getMessages(const int & start, const int & begin, const int & idChat, const function<void(vector<Message> &)> & callback) {}
    void addChat(ChatRoom & room, const function<void(const ChatRoom &, optional<string> &)> & callback) {}
    bool check() {}
private:
    AppNetwork();
    static optional<shared_ptr<AppNetwork>> single;
    unique_ptr<Announcer> announcer;
    unique_ptr<AbstractCache> cache;
    shared_ptr<AbstractClient> client;
};



#endif //NETLIB_APPNETWORK_H
