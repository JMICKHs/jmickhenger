#include <iostream>
#include "announcer/Announcer.h"
#include "client/Client.h"
#include <ctime>
#include "AppNetwork.h"
// мэин тут только для проверки, эта часть проекта должна быть либой
using namespace std;
using namespace inf;
int main() {
//    // testAnnounser
//    Announcer a;
//    a.addCallback(13, [](ChatChange change) {
//        cout << change.idChat << " chat!\n";
//    });
//    a.addCallback(12, [](ChatChange change) {
//        cout << change.idChat << " chat!\n";
//    });
//    a.addCallback(14, [](ChatChange change) {
//        cout << change.idChat << " chat!\n";
//    });
//    a.setGeneralCallback([](ChatChange change) {
//        cout << change.idChat << " chat! text from general\n";
//    });
//    ChatChange test;
//    test.idChat = 0;
//    a.notify(test);

//    //test client
//    try {
//            auto client = Client::shared();
//            client->setMsgHandler([](const string & str) {
//                cout << "from server: " << str << endl;
//            });
//            client->run();
//            string msg;
//            while (getline(std::cin, msg)) {
//                client->write(msg);
//            }
//            client->close();
//    }
//    catch (std::exception& e) {
//        std::cerr << "Exception: " << e.what() << "\n";
//    }

//    //test parser
//    Parser p;
//    p.addInt(7, "id");
//    p.addStr("teststr", "err");
//    p.addBool(false, "key");
//    cout << p.getRes() << " \n";
//    cout << "-----------\n";
//    cout << "id - " << p.getInt("id") << endl;
//    cout << "-----------\n";
//    p.clear();
//    vector<int> tmp1 = {1, 2, 3, 7, 8};
//    p.addArrInt(tmp1, "arrInt");
//    vector<string> tmp2 = {"lol", "kek", "cheb", "lalal", "alalla"};
//    p.addArrStr(tmp2, "names");
//    cout << p.getRes();
//    cout << "-----------\n";
//    vector<int> test3 = p.getArrInt("arrInt");
//    for(const auto & item : test3) {
//        cout << item << " ";
//    }
//    cout << "\n";
//    cout << "names = " << p.getChild("names");
//    cout << "-----------\n";

//    //test codeble
//    MyAccount acc(3, "testUser", "NIL", "1234", {1, 3, 18}, {167, 189});
//    string json = acc.encode();
//    cout << json << endl;
//    MyAccount acc2;
//    acc2.decode(json);
//
//    UserInfo user(178, "178user", "NIL");
//    json = user.encode();
//    cout << json << endl;
//    UserInfo user2;
//    user2.decode(json);

//    string json;
//    Message msg(56, 3, "text from me", 56, time(NULL), false);
//    json = msg.encode();
//    cout << json << endl;
//    Message msg2;
//    msg2.decode(json);

//    ChatInfo info(3, "myChat");
//    string json;
//    json = info.encode();
//    cout << json << endl;
//    ChatInfo info2;
//    info2.decode(json);
//    cout << info2.encode();

//    string json;
//    ChatRoom room(4, "myChat", {3, 6, 7}, {7});
//    json = room.encode();
//    cout << json << endl;
//    ChatRoom room2;
//    room2.decode(json);
//    cout << room2.encode() << endl;

//    string json;
//    Message msg(56, 3, "text from me", 56, time(NULL), false);
//    ChatChange change(4, "add", {msg, msg, msg});
//    json = change.encode();
//    cout << json << endl;
//    ChatChange change2;
//    change2.decode(json);
//    cout << change2.encode();

//    string json;
//    Message msg(56, 3, "text from me", 56, time(NULL), false);
//    ChatChange change(4, "add", {msg, msg, msg});
//    Reply reply("", 0, 2, change.encode());
//    json = reply.encode();
//    cout << json << endl;
//    Reply reply2;
//    reply2.decode(json);
//    cout << reply2.encode() << endl;

//    auto net = AppNetwork::shared();
//    while(true) {
//
//    }
    return 0;
}
