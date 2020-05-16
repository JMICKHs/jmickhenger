#include <iostream>
#include "netlib/announcer/Announcer.h"
#include "netlib/client/Client.h"
#include <ctime>
#include "netlib/AppNetwork.h"


using namespace std;
using namespace inf;

int main() {

//    Message msg(78, 6, "msg number 6 for 78 chat from 99 user", 99, time(nullptr), false);
//    cout << msg.encode();
    auto net = AppNet::shared();
    net->runClient([](int ec) {
        cout << "connection err code - " << ec << endl;
    });
    int c = 0;
    int idUser = 78;
    net->auth("newTestUser", "12345", [](MyAccount & acc, optional<string> &) {
        cout << acc.login << " смог ввойти в чат!\n";
    });
    string text;
    while(getline(cin, text)) {
        Message msg;
        msg.text = text;
        net->sendMsg(msg, [](optional<string> &){

        });
    }
    net->stopClient();
    return 0;
}
