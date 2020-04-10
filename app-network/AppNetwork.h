//
// Created by Sergei Alexeev on 11.04.2020.
//

#ifndef APP_NETWORK_APPNETWORK_H
#define APP_NETWORK_APPNETWORK_H

#include "announser/Announser.h"
#include "client/Client.h"
#include "info/Info.h"
#include <string>
#include <functional>
#include <vector>

using namespace std;

class AppNetwork {
public:
    AppNetwork * shared();
    void login(string name, string password, const function<void(MyAccount)> callback);
    void registration(MyAccount acc, const function<void(int)> callback); //если id == 0, то неудачно
    void getListChat(unsigned int idUser, const function<void(vector<ChatInfo>)> callback);
    void getChatRoom(unsigned int idChat, const function<void(ChatRoom)> callback);
    void setObserverChat(unsigned int idChat, const function<void(ChatChange)> callback);
    void sendMessage(Message msg, const function<void(bool)> callback); // отправилось или нет bool
    void getUser(unsigned int id, const function<void(UserInfo)> callback);
    void getMyAccount(MyAccount acc, const function<void(MyAccount)> callback);
    void saveAvatar(string path, const function<void(bool)> callback); // отправилось или нет bool
private:
    AppNetwork * singleton = nullptr;
    Announser announser;
};


#endif //APP_NETWORK_APPNETWORK_H
