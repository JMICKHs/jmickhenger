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
#include <unordered_map>

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
    bool check() {} //TODO
    void auth(const string & login, const string & pass, const function<void(MyAccount &, errstr &)> & callback);
    void registration(const MyAccount & acc, const function<void(int, errstr &)>& callback);
    void getListChat(int idUser, const function<void(vector<ChatInfo> &, errstr &)> & callback);
    void getChatRoom(int idChat, const function<void(ChatRoom &, errstr &)> & callback);
    void sendMsg(const Message & msg, const function<void(errstr &)> & callback);
    void setObserverChat(int idChat, const function<void(ChatChange &)>& callback);
    void setObserverUnknownChat(const function<void(ChatChange &)>& callback);
    void getMsgs(int idChat, int start, int end, const function<void(vector<Message> &, errstr &)> & callback);
    void getLastMsg(int idChat, const function<void(Message &, errstr &)> & callback){}//TODO
    void addFrnd(int idFrnd, const function<void(errstr &)> & callback){}//TODO
    void getListFrnd(int id, const function<void(vector<int> &, errstr &)> & callback){}//TODO
    void getInfoMe(int id, const function<void(MyAccount &, errstr &)> & callback){}//TODO
    void getUser(int id, const function<void(UserInfo &, errstr &)> & callback){}//TODO
    void createChat(const ChatRoom & room, const function<void(int, errstr &)> & callback){}//TODO
    void addAdminChat(int idChat, int idUser, const function<void(errstr &)> & callback){}//TODO
    void dellChat(int idChat, const function<void(errstr &)> & callback){}//TODO
    void dellMsg(int idChat, int numberMsg, const function<void(errstr &)> & callback){}//TODO
    void changeMsg(const Message & msg, const function<void(errstr &)> & callback){}//TODO
    void saveAvatar(const string & path, const function<void(errstr &)> & callback){}//TODO
    void changeMe(const inf::MyAccount & acc, const function<void(errstr &)> & callback){}//TODO
private:
    AppNet();
    void readHandler(const string & str);
    void setHandlers();
    static optional<shared_ptr<AppNet>> single;
    unique_ptr<Announcer> announcer;
    unique_ptr<AbstractCache> cache; //TODO
    shared_ptr<AbstractClient> client;
    unordered_map<int, function<void(int, errstr &, const string &)>> handlers;
    // почему unoredered? в среднем работает за O(1) и мы не меняем в нём данные, поэтому худшего случая не будет
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
        delFrnd = 11,
        getMe = 12,
        getUser = 13,
        createChat = 14,
        delChat = 15,
        saveAvatar = 16,
        changeUser = 17,
        changeMessage = 18,
        delMessage = 19,
        changeChat = 20,
        test = 21,
    };
};

#endif //NETLIB_APPNETWORK_H
