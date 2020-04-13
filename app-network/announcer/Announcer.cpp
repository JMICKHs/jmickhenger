//
// Created by Sergei Alexeev on 11.04.2020.
//

#include "Announcer.h"

Announcer::Announcer() = default;

void Announcer::addCallback(unsigned int idChat, const function<void(const Info::ChatChange)>& callback) {
    callbacks.insert(pair(idChat, callback));
}

void Announcer::notify(Info::ChatChange change) {
//    const function<void(const ChatChange)> f = callbacks[change.idChat];
//    f(change);
}