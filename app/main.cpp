#include <iostream>
#include "netlib/announcer/Announcer.h"
#include "netlib/client/Client.h"
#include <ctime>
#include "netlib/AppNetwork.h"


using namespace std;
using namespace inf;

int main() {
//    //client work test
    auto net = AppNet::shared();
    net->runClient([](int ec) {
        cout << "connection err code - " << ec << endl;
    });
    int c = 0;
    int idUser = 78;
    string text;

//    while(getline(cin, text)) {
//        Message msg(idUser, c++, text, 56, time(nullptr), false);
//        net->sendMsg(msg, [c](optional<string> &){
//            cout << "вызвался в " << c << "раз\n";
//        });
//    }

    net->auth("vasia", "12345", [](MyAccount & acc, optional<string> &) {
        cout << acc.login << " смог ввойти в чат!\n";
    });
    sleep(2);
    //(int idUser, const function<void(vector<ChatInfo> &, errstr &)> & callback);
    net->getListChat(4, [](vector<ChatInfo> & a, optional<string> &) {
        cout << "чаты\n";
        for(const auto & item : a) {
            cout << item.name << endl;
        }
    });
    sleep(2);
    net->stopClient();

//    announser work test
//    Announcer an;
//    ChatInfo info(3, "name");
//    ChatInfo info2(5, "name");
//    int cmd = 5;
//    function<void(int)> f = [](int n){
//        cout << "n - " << n << endl;
//    };
//    int context = 7;
//    an.addCallback<int, int>(cmd, context, f);
//
//
//    auto ftest = an.getCallback<int, int>(cmd, context);
//    if (ftest) {
//        ftest.value()(5);
//    }
//    auto ftest2 = an.getCallback<int, int>(cmd, context);
//    if (!ftest2) {
//        cout << "Всё верно, тут ничего быть не должно" << endl;
//    }
    return 0;
}
