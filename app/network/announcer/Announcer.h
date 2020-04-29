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
    Announcer();
    ~Announcer();
    void addCallback(const int & idChat, const function<void(const inf::ChatChange)>& callback);
    void setGeneralCallback(const function<void(const inf::ChatChange)>& callback);
    void notify(inf::ChatChange & change);
private:
    std::map<int, std::function<void(inf::ChatChange)>> callbacks;
    std::optional<function<void(const inf::ChatChange)>> generalCallback;
};


#endif //NETWORK_ANNOUNCER_H
