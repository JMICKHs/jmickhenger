//
// Created by Sergei Alexeev on 11.04.2020.
//

#include "Announcer.h"

Announcer::Announcer() = default;

void Announcer::addCallback(unsigned int idChat, const function<void(const ChatChange)> &callback) {
    callbacks.insert(pair(idChat, callback));
}

void Announcer::notify(ChatChange change) {
    function f = callbacks[change.idChat];
    f(change);
}
