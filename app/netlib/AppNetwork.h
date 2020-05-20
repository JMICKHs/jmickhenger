//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_APPNETWORK_H
#define NETLIB_APPNETWORK_H

#import <unordered_map>

#include "announcer/Announcer.h"
#include "client/Client.h"
#include "cache/Cache.h"

using errstr = std::optional<std::string>;

class AppNet: public std::enable_shared_from_this<AppNet> {
public:
    AppNet(const AppNet &other) = delete;
    AppNet(AppNet &&other) = delete;
    AppNet& operator=(const AppNet &other) = delete;
    AppNet& operator=(AppNet &&other) = delete;
    static std::shared_ptr<AppNet> shared();
    void runClient(const std::function<void(int)> & errHandler);
    void stopClient();
    bool check() {} //TODO
    std::optional<inf::MyAccount> accFromCache();
    void setClientDelegate(std::shared_ptr<AbstractClient> client); //для мок клиента в тестировании
    void auth(const std::string & login, const std::string & pass, const std::function<void(inf::MyAccount &, errstr &)> & callback);
    void registration(const inf::MyAccount & acc, const std::function<void(int, errstr &)>& callback);
    void getListChat(int idUser, const std::function<void(std::vector<inf::ChatInfo> &, errstr &)> & callback);
    void getChatRoom(int idUser, int idChat, const std::function<void(inf::ChatRoom &, errstr &)> & callback);
    void sendMsg(const inf::Message & msg, const std::function<void(int number, errstr &)> & callback);
    void setObserverChat(int idChat, const std::function<void(inf::ChatChange &)>& callback);
    void setObserverUnknownChat(const std::function<void(inf::ChatChange &)>& callback);
    void getMsgs(int idUser, int idChat, int start, int end, const std::function<void(std::vector<inf::Message> &, errstr &)> & callback);
    void getLastMsg(int idUser, int idChat, const std::function<void(inf::Message &, errstr &)> & callback);
    void addFrnd(int idUser, int idFrnd, const std::function<void(errstr &)> & callback);
    void addFrndNick(int idUser, const std::string & nick, const std::function<void(errstr &)> & callback); //TODO
    void getListFrnd(int id, const std::function<void(std::vector<int> &, errstr &)> & callback);
    void delFrnd(int idUser, int idFrnd, const std::function<void(errstr &)> & callback);
    void getInfoMe(int id, const std::function<void(inf::MyAccount &, errstr &)> & callback);
    void getUser(int myId, int id, const std::function<void(inf::UserInfo &, errstr &)> & callback);
    void createChat(const inf::ChatRoom & room, const std::function<void(int, errstr &)> & callback);
    void addAdminChat(int myId, int idChat, int idUser, const std::function<void(errstr &)> & callback){}//TODO
    void dellChat(int idUser, int idChat, const std::function<void(errstr &)> & callback){}//TODO
    void dellMsg(int idUser, int idChat, int numberMsg, const std::function<void(errstr &)> & callback);
    void changeMsg(int idUser, const inf::Message & msg, const std::function<void(errstr &)> & callback);
    void changeMe(const inf::MyAccount & acc, const std::function<void(errstr &)> & callback){}//TODO
private:
    explicit AppNet();
    void readHandler(const std::string & str);
    void setHandlers();
    std::unique_ptr<Announcer> announcer;
    std::shared_ptr<AbstractCache> cache;
    std::shared_ptr<AbstractClient> client;
    std::unordered_map<int, std::function<void(int, errstr &, const std::string &)>> handlers;
    // почему unoredered? в среднем работает за O(1) и мы не меняем в нём данные, поэтому худшего случая не будет
    bool clientStarted = false;
    enum class Cmds: int {
        registration = 1,
        auth, //2
        getListChat, // 3
        getChatRoom, // 4
        sendMessage, // 5
        getMessages, // 6
        incomingMsgs, // 7
        getLastMsg, //8
        addFrnd, //9
        getListFrnd, // 10
        delFrnd, // 11
        getMe, // 12
        getUser, // 13
        createChat, // 14
        delChat, //15
        addFrndNick, //16
        changeUser, //17
        changeMessage, //18
        delMessage, //19
        changeChat, //20
        test, //21
    };
};

#endif //NETLIB_APPNETWORK_H
