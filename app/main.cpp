#include <fstream>
#include <ctime>
#include <sstream>

#include "netlib/AppNetwork.h"

using namespace std;
using namespace inf;

void setInfoFromConfig(optional<string> & login, optional<string> & pas, optional<int> & idChat);

int main() {
    //пример авторизации и написания сообщений в определенный чат
    
    auto net = AppNet::shared();
    net->runClient([](int ec){
        cout << "ошибка соеденеия номер - " << ec << endl;
    });
    optional<string> login, pas;
    optional<int> idChat;
    setInfoFromConfig(login, pas, idChat);
    if(!login || !pas) {
        cout << " Неправильный сonfig\n";
        return 0;
    }
    net->auth(login.value(), pas.value(), [net](const MyAccount & acc, errstr& er){
        if(!er) {
            cout << acc.login << " авторизировался !\n";
        } else {
            cout << "ошибка авторизации: " << er.value() << endl;
            net->stopClient();
        }
    });
    if(!idChat) {
        cout << " Неправильный сonfig\n";
        return 0;
    }
    string text;
    while(getline(cin, text)) {
        Message msg;
        msg.text = text;
        net->sendMsg(msg, [net](errstr & er){
            if(!er) {
                cout << "сообщение доставлено!\n";
            } else {
                cout << "ошибка отправки сообщения: " << er.value() << endl;
                net->stopClient();
            }
        });
    }
    net->stopClient();
    return 0;
}

void setInfoFromConfig(optional<string> & login, optional<string> & pas, optional<int> & idChat) {
    static string fileConfig = "../netlib/configs/testUserConfig";
    static string keyLogin = "LOGIN:";
    static string keyPas = "PASSWORD:";
    static string keyIdChat = "IDCHAT:";
    ifstream conf(fileConfig);
    string line;
    getline(conf, line);
    if(line == keyLogin) {
        getline(conf, line);
        login = line;
    } else {
        login = nullopt;
    }
    getline(conf, line);
    if(line == keyPas) {
        getline(conf, line);
        pas = line;
    } else {
        pas = nullopt;
    }
    getline(conf, line);
    if(line == keyIdChat) {
        getline(conf, line);
        idChat = atoi(line.data());
    } else {
        idChat = nullopt;
    }

}