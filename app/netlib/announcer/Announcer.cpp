#include "Announcer.h"

using namespace std;
using namespace inf;

Announcer::Announcer() {
    generalCallback = nullopt;
}

Announcer::~Announcer() {
    generalCallback = nullopt;
    callbacks.clear();
}

void Announcer::addCallback(const int &idChat, const function<void(const inf::ChatChange &)> &callback) {
    callbacks[idChat] = callback;
}

void Announcer::setGeneralCallback(const function<void(const inf::ChatChange &)> &callback) {
    generalCallback = callback;
}

void Announcer::notify(const inf::ChatChange &change) {
    if(callbacks.count(change.idChat)) {
        callbacks[change.idChat](change);
    } else if(generalCallback) {
        generalCallback.value()(change);
    }
}