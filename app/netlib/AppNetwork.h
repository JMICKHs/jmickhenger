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
#include <mutex>

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
    AppNet(const AppNet &other) = delete;
    AppNet(AppNet &&other) = delete;
    static shared_ptr<AppNet> shared();
    void runClient(const function<void(int)> & errHandler);
    void stopClient();
    bool check();
    void auth(const string & login, const string & pass, const function<void(MyAccount &, errstr &)> & callback);
    void registration(const MyAccount & acc, const function<void(int, errstr &)>& callback);
    void getListChat(int idUser, const function<void(vector<ChatInfo> &, errstr &)> & callback);
    void getChatRoom(int idChat, const function<void(ChatRoom &, errstr &)> & callback);
    void sendMsg(const Message & msg, const function<void(bool, errstr &)> & callback);
    void setObserverChat(int idChat, const function<void(ChatChange &)>& callback);
    void setObserverUnknownChat(const function<void(ChatChange &)>& callback);
    void getMsgs(int idChat, int start, int end, const function<void(vector<Message> &, errstr &)> & callback);
    void getLastMsg(int idChat, const function<void(Message &, errstr &)> & callback);
    void addFrnd(int idFrnd, const function<void(bool, errstr &)> & callback);
    void getListFrnd(int id, const function<void(vector<int> &, errstr &)> & callback);
    void getInfoMe(int id, const function<void(MyAccount &, errstr &)> & callback);
    void getUser(int id, const function<void(UserInfo &, errstr &)> & callback);
    void createChat(ChatRoom & room, const function<void(int, errstr &)> & callback);
    void addAdminChat(int idChat, int idUser, const function<void(bool, errstr &)> & callback);
    void dellChat(int idChat, const function<void(bool, errstr &)> & callback);
    void dellMsg(int idChat, int numberMsg, const function<void(bool, errstr &)> & callback);
    void changeMsg(const Message & msg, const function<void(bool, errstr &)> & callback);
    void saveAvatar(const string & path, const function<void(bool, errstr &)> & callback);
    void changeMe(const inf::MyAccount & acc, const function<void(bool, errstr &)> & callback);
private:
    AppNet();
    static optional<shared_ptr<AppNet>> single;
    unique_ptr<Announcer> announcer;
    unique_ptr<AbstractCache> cache;
    shared_ptr<AbstractClient> client;
    static std::mutex mtx;
};

#endif //NETLIB_APPNETWORK_H
