#include <iostream>
#include "announcer/Announcer.h"
// мэин тут только для проверки, эта часть проекта должна быть либой
using namespace std;
using namespace inf;
int main() {
    Announcer a;
    a.addCallback(13, [](ChatChange change) {
        cout << change.idChat << " chat!\n";
    });
    a.addCallback(12, [](ChatChange change) {
        cout << change.idChat << " chat!\n";
    });
    a.addCallback(14, [](ChatChange change) {
        cout << change.idChat << " chat!\n";
    });
    a.setGeneralCallback([](ChatChange change) {
        cout << change.idChat << " chat! text from general\n";
    });
    ChatChange test;
    test.idChat = 0;
    a.notify(test);
    return 0;
}
