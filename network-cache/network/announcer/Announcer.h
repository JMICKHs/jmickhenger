//
// Created by Sergei Alexeev on 13.04.2020.
//

#ifndef NETWORK_CACHE_ANNOUNCER_H
#define NETWORK_CACHE_ANNOUNCER_H


#include <map>
#include <functional>
#include "../info/Info.h"


class Announcer {
public:
    Announcer();
    void addCallback(unsigned int idChat, const function<void(const Info::ChatChange)>& callback);
    void notify(Info::ChatChange change);
private:
    map<unsigned int, const function<void(const Info::ChatChange)>& > callbacks;
};


#endif //NETWORK_CACHE_ANNOUNCER_H
