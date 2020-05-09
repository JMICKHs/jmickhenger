//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_ANNOUNCER_H
#define NETLIB_ANNOUNCER_H


#include <map>
#include <functional>
#include <optional>
#include "../info/Info.h"

class Announcer {
public:
    Announcer();
    ~Announcer();
    void addChatCallback(int idChat, const function<void(inf::ChatChange &)>& callback);
    void setChatAnonCallback(const function<void(inf::ChatChange &)>& callback);
    void notifyChat(inf::ChatChange & change);
    template<typename Context, typename... Args>
    void addCallback(int cmd, Context & context, const function<void(Args...)>& callback) {
        auto item = pair<void *, void *>((void *)&context, (void *)&callback);
        callbacks.insert(pair<int, pair<void *, void *>>(cmd, item));
    }
    template<typename Context, typename... Args>
    optional<function<void(Args...)>> getCallback(int cmd, Context & context) {
        auto iterPair = callbacks.equal_range(cmd);
        for (; iterPair.first != iterPair.second; iterPair.first++) {
            auto tmpIter = iterPair.first;
            Context * itemContext = (Context *)tmpIter->second.first;
            if(context == *itemContext) {
                auto tmpF = tmpIter->second.second;
                auto f = reinterpret_cast<function<void(Args...)> *>(tmpF);
                return *f;
            }
        }
        return nullopt;
    }
private:
    std::map<int, std::function<void(inf::ChatChange &)>> chatCallbacks;
    std::optional<function<void(inf::ChatChange &)>> generalCallback; // для обработки чатов, о которых юзер пока не знает
    std::multimap<int, pair<void *, void *>> callbacks; // для хранения различных callback
    // первый void * - контекст
    // второй void * - callback
};


#endif //NETLIB_ANNOUNCER_H
