#import <fstream>
#import <ctime>
#import <sstream>

#include "netlib/AppNetwork.h"

using namespace std;
using namespace inf;

void setInfoFromConfig(optional<string> & login, optional<string> & pas);

int main() {
    //пример авторизации и написания сообщений в определенный чат
    auto cache = Cache::shared();
    auto net = AppNet::shared();
    net->runClient([](int ec){
        cout << "ошибка соеденеия номер - " << ec << endl;
        cout << "ошибка номер - " << ec << endl;
    });
    optional<string> login, pas;
    setInfoFromConfig(login, pas);
    if(!login || !pas) {
        cout << " Неправильный сonfig\n";
        return 0;
    }
    net->auth(login.value(), pas.value(), [](const MyAccount & acc, errstr& er){
        if(!er) {
            cout << acc.login << " авторизовался!\n";
        } else {
            cout << "ошибка авторизации: " << er.value() << endl;
            AppNet::shared()->stopClient();
        }
    });
    sleep(3);
    net->stopClient();
    return 0;
}

void setInfoFromConfig(optional<string> & login, optional<string> & pas) {
    static string fileConfig = "../netlib/configs/testUserConfig";
    static string keyLogin = "LOGIN:";
    static string keyPas = "PASSWORD:";
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
}