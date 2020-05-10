//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_APPNETWORK_H
#define NETLIB_APPNETWORK_H


#include "announcer/Announcer.h"
#include <boost/bind.hpp>
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

using errstr = optional<string>;

class AppNet: public enable_shared_from_this<AppNet> {
public:
    AppNet(const AppNet &other) = delete;
    AppNet(AppNet &&other) = delete;
    static shared_ptr<AppNet> shared();
    void runClient(const function<void(int)> & errHandler);
    void stopClient();
    bool check();
    void auth(const string & login, const string & pass, const function<void(MyAccount &, errstr &)> & callback);
    //
    void registration(const MyAccount & acc, const function<void(int, errstr &)>& callback);
    //
    void getListChat(int idUser, const function<void(vector<ChatInfo> &, errstr &)> & callback);
    //
    void getChatRoom(int idChat, const function<void(ChatRoom &, errstr &)> & callback);
    //
    void sendMsg(const Message & msg, const function<void(errstr &)> & callback);
    void setObserverChat(int idChat, const function<void(ChatChange &)>& callback);
    void setObserverUnknownChat(const function<void(ChatChange &)>& callback);
    void getMsgs(int idChat, int start, int end, const function<void(vector<Message> &, errstr &)> & callback);
    //
    void getLastMsg(int idChat, const function<void(Message &, errstr &)> & callback);
    //
    void addFrnd(int idFrnd, const function<void(errstr &)> & callback);
    void getListFrnd(int id, const function<void(vector<int> &, errstr &)> & callback);
    void getInfoMe(int id, const function<void(MyAccount &, errstr &)> & callback);
    //
    void getUser(int id, const function<void(UserInfo &, errstr &)> & callback);
    //
    void createChat(const ChatRoom & room, const function<void(int, errstr &)> & callback);
    //
    void addAdminChat(int idChat, int idUser, const function<void(errstr &)> & callback);
    //
    void dellChat(int idChat, const function<void(errstr &)> & callback);
    //
    void dellMsg(int idChat, int numberMsg, const function<void(errstr &)> & callback);
    //
    void changeMsg(const Message & msg, const function<void(errstr &)> & callback);
    //
    void saveAvatar(const string & path, const function<void(errstr &)> & callback);
    void changeMe(const inf::MyAccount & acc, const function<void(errstr &)> & callback);
    //
private:
    AppNet();
    void readHandler(const string & str);
    static optional<shared_ptr<AppNet>> single;
    unique_ptr<Announcer> announcer;
    unique_ptr<AbstractCache> cache;
    shared_ptr<AbstractClient> client;
    static std::mutex mtx;
    bool clientStarted = false;
    enum class Cmds {
        registration = 1,
        auth = 2,
        getListChat = 3,
        getChatRoom = 4,
        sendMessage = 5,
        getMessages = 6,
        incomingMsgs = 7,
        getLastMsg = 8,
        addFrnd = 9,
        getListFrnd = 10,
        getMe = 11,
        getUser = 12,
        createChat = 13,
        saveAvatar = 14,
        changeUser = 15,
        changeMessage = 16,
        changeChat = 17,
        testSystem = 18,
    };
};

#endif //NETLIB_APPNETWORK_H
