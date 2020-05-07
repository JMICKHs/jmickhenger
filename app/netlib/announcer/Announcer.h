//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_ANNOUNCER_H
#define NETLIB_ANNOUNCER_H


#include <map>
#include <functional>
#include "../info/Info.h"

class Announcer {
public:
    Announcer();
    ~Announcer();
    void addCallback(const int & idChat, const function<void(const inf::ChatChange &)>& callback);
    void setGeneralCallback(const function<void(const inf::ChatChange &)>& callback);
    void notify(const inf::ChatChange & change);
private:
    std::map<int, std::function<void(const inf::ChatChange &)>> callbacks;
    std::optional<function<void(const inf::ChatChange &)>> generalCallback; // для обработки чатов, о которых юзер пока не знает
};


#endif //NETLIB_ANNOUNCER_H
