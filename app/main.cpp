#include <iostream>
#include "netlib/announcer/Announcer.h"
#include "netlib/client/Client.h"
#include <ctime>
#include "netlib/AppNetwork.h"


using namespace std;
using namespace inf;
int main() {
    auto net = AppNet::shared();
    net->runClient([](int ec) {
        cout << "connection err code - " << ec << endl;
    });
    int c = 0;
    int idUser = 78;
    string text;

    while(getline(cin, text)) {
        Message msg(idUser, c++, text, 56, time(NULL), false);
        net->sendMsg(msg, [](const bool &, optional<string> &){

        });
    }
    net->stopClient();
    return 0;
}
