//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_ANNOUNCER_H
#define NETWORK_ANNOUNCER_H


#include <map>
#include <functional>
#include "../info/Info.h"

class Announcer {
public:
    Announcer() {}
    void addCallback(const unsigned int & idChat, const function<void(const inf::ChatChange)>& callback) {}
    void notify(inf::ChatChange & change) {}
private:
    map<unsigned int, const function<void(const inf::ChatChange)>& > callbacks;
};


#endif //NETWORK_ANNOUNCER_H
