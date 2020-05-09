#include <iostream>
#include "netlib/announcer/Announcer.h"
#include "netlib/client/Client.h"
#include <ctime>
#include "netlib/AppNetwork.h"


using namespace std;
using namespace inf;
int main() {

//    //client work test
//    auto net = AppNet::shared();
//    net->runClient([](int ec) {
//        cout << "connection err code - " << ec << endl;
//    });
//    int c = 0;
//    int idUser = 78;
//    string text;
//
//    while(getline(cin, text)) {
//        Message msg(idUser, c++, text, 56, time(NULL), false);
//        net->sendMsg(msg, [](const bool &, optional<string> &){});
//    }
//    net->stopClient();

    //announser work test
    Announcer an;
    ChatInfo info(3, "name");
    ChatInfo info2(5, "name");
    int cmd = 5;
    function<void(int)> f = [](int n){
        cout << "n - " << n << endl;
    };
    an.addCallback<ChatInfo, int>(cmd, info, f);

    auto ftest = an.getCallback<ChatInfo, int>(cmd, info);
    if (ftest) {
        ftest.value()(5);
    }
    auto ftest2 = an.getCallback<ChatInfo, int>(cmd, info2);
    if (!ftest2) {
        cout << "Всё верно, тут ничего быть не должно" << endl;
    }
    return 0;
}
