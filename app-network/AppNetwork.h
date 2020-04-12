//
// Created by Sergei Alexeev on 11.04.2020.
//

#ifndef APP_NETWORK_APPNETWORK_H
#define APP_NETWORK_APPNETWORK_H

#include "announcer/Announcer.h"
#include "client/Client.h"
#include <string>
#include <functional>
#include <vector>

using namespace std;

class AppNetwork {
public:
    ~AppNetwork();
    static AppNetwork * shared();
    void login(string name, string password, const function<void(const MyAccount)>& callback);
    void registration(MyAccount acc, const function<void(const int)>& callback); //если id == 0, то неудачно
    void getListChat(unsigned int idUser, const function<void(const vector<ChatInfo>)>& callback);
    void getChatRoom(unsigned int idChat, const function<void(const ChatRoom)>& callback);
    void setObserverChat(unsigned int idChat, const function<void(const ChatChange)>& callback);
    void sendMessage(Message msg, const function<void(const bool)>& callback); // отправилось или нет bool
    void getUser(unsigned int id, const function<void(const UserInfo)>& callback);
    void getMyAccount(MyAccount acc, const function<void(const MyAccount)>& callback);
    void saveAvatar(string path, const function<void(const bool)>& callback); // отправилось или нет bool
    bool check();
private:
    static AppNetwork * singleton;
    Announcer announcer;
    Client client;
    AppNetwork();
};


#endif //APP_NETWORK_APPNETWORK_H
