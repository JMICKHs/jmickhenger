//
// Created by Sergei Alexeev on 11.04.2020.
//

#ifndef APP_NETWORK_ANNOUNCER_H
#define APP_NETWORK_ANNOUNCER_H

#include <map>
#include <functional>
#include "../info/Info.h"


class Announcer {
public:
    Announcer();
    void addCallback(unsigned int idChat, const function<void(const ChatChange)>& callback);
    void notify(ChatChange change);
private:
    map<unsigned int, const function<void(const ChatChange)>& > callbacks;
};


#endif //APP_NETWORK_ANNOUNCER_H
