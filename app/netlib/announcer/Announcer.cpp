#include "Announcer.h"

using namespace std;
using namespace inf;

Announcer::Announcer() {
    generalCallback = nullopt;
}

Announcer::~Announcer() {
    generalCallback = nullopt;
    chatCallbacks.clear();
}

void Announcer::addChatCallback(int idChat, const function<void(inf::ChatChange &)> &callback) {
    chatCallbacks[idChat] = callback;
}

void Announcer::setChatAnonCallback(const function<void(inf::ChatChange &)> &callback) {
    generalCallback = callback;
}

void Announcer::notifyChat(inf::ChatChange &change) {
    if(chatCallbacks.count(change.idChat)) {
        chatCallbacks[change.idChat](change);
    } else if(generalCallback) {
        generalCallback.value()(change);
    }
}