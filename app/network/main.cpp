#include <iostream>
#include "announcer/Announcer.h"
#include "client/Client.h"
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

    //test client
    try {
            auto client = Client::shared();
            client->setMsgHandler([](const string & str) {
                cout << "from server: " << str << endl;
            });
            client->run();
            string msg;
            while (getline(std::cin, msg)) {
                client->write(msg);
            }
            client->close();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
