//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_APPNETWORK_H
#define NETWORK_APPNETWORK_H


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

class AbstractNetwork {
public:
    AbstractNetwork() = default;
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

//class AppNetwork: AbstractNetwork {
//public:
//    AppNetwork(const AppNetwork &other) = delete;
//    AppNetwork(AppNetwork &&other) = delete;
//    AppNetwork& operator=(const AppNetwork &other) = delete;
//    AppNetwork& operator=(AppNetwork &&other) = delete;
//    ~AppNetwork();
//    static shared_ptr<AppNetwork> shared();
//    void setClietnDelegate(const AbstractClient & clientDelegate) {}
//    optional<MyAccount> getMe() override;
//    void login(const string & name, const string & password, const function<void(const MyAccount &)> & callback) override;
//    void registration(const MyAccount & acc, const function<void(const int &)>& callback) override;//если id == 0, то неудачно
//    void getListChat(const int & idUser, const function<void(const vector<ChatInfo> &)> & callback) override;
//    void getChatRoom(const int & idChat, const function<void(const ChatRoom &)> & callback) override;
//    void setObserverChat(const int & idChat, const function<void(const ChatChange &)>& callback) override;
//    void sendMessage(const Message & msg, const function<void(const bool &)> & callback) override; // отправилось или нет bool
//    void getUser(const int & id, const function<void(const UserInfo &)> & callback) override;
//    void saveMyAvatar(const string &path, const function<void(const string &)> & callback) override;// отправилось или нет bool
//    void getMessages(const int & start, const int & begin, const int & amount, const function<void(vector<Message> &)> & callback) override;
//    void addChat(ChatRoom & room, const function<void(const ChatRoom &)> & callback) override;
//    bool check() override;
//private:
//    AppNetwork();
//    static AppNetwork * singleton;
//    Announcer announcer;
//    AbstractCache * cache;
//    AbstractClient * client;
//};

//AppNetwork * AppNetwork::singleton = nullptr;

#endif //NETWORK_APPNETWORK_H