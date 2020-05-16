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
//
//    MyAccount acc;
//    acc.login = "testUser";
//    acc.password = "12321";
//    net->registration(acc, [](int id, optional<string> &){
//        cout << "Я получил id - " << id << endl;
//    });
//    sleep(4);
    net->auth("vasadhsadjh", "12345", [](MyAccount & acc, optional<string> &) {
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
//    sleep(4);
//    net->getListChat(4, [](vector<ChatInfo> & a, optional<string> &) {
//        cout << "чаты\n";
//        for(const auto & item : a) {
//            cout << item.name << endl;
//        }
//    });
//
//    sleep(1);
//    net->getLastMsg(3, [](Message & msg, optional<string> &){
//        cout << "посл сообщение " << msg.text << endl;
//    });
//    sleep(1);
//    net->getMsgs(3, 0, 2, [](vector<Message> & msgs, optional<string> &){
//        cout << "получил " << msgs.size() << endl;
//    });
//
//    sleep(3);
//







//    string text;
//
//    while(getline(cin, text)) {
//        Message msg(idUser, c++, text, 56, time(nullptr), false);
//        net->sendMsg(msg, [c](optional<string> &){
//            cout << "вызвался в " << c << "раз\n";
//        });
//    }


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
