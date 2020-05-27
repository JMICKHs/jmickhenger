//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_ANNOUNCER_H
#define NETLIB_ANNOUNCER_H

#import <map>
#import <functional>
#import <optional>
#import <memory>

#include "../info/Info.h"

class Announcer {
public:
    Announcer();
    ~Announcer();
    void addChatCallback(int idChat, const std::function<void(inf::ChatChange &)>& callback);
    void setChatAnonCallback(const std::function<void(inf::ChatChange &)>& callback);
    void notifyChat(inf::ChatChange & change);
    template<typename Context, typename... Args>
    void addCallback(int cmd, Context context, const std::function<void(Args...)>& callback) {
        auto tmpContext = std::make_shared<Context>(context);
        auto item = std::pair<std::shared_ptr<void>, void *>(std::move(tmpContext), (void *)&callback); //value - контекст и функция
        callbacks.insert(std::pair<int, std::pair<std::shared_ptr<void>, void *>>(cmd, item));
    }
    template<typename Context, typename... Args>
    std::optional<std::function<void(Args...)>> getCallback(int cmd, Context context) {
        auto iterPair = callbacks.equal_range(cmd);
        for (; iterPair.first != iterPair.second; ++iterPair.first) {
            auto tmpIter = iterPair.first;
            Context * itemContext = (Context *)tmpIter->second.first.get();
            if(context == *itemContext) {
                auto tmpF = tmpIter->second.second; // берем указатель void на функцию
                auto f = reinterpret_cast<std::function<void(Args...)> *>(tmpF); // возвращаем тип на нужный
                callbacks.erase(tmpIter); // удаляем пару ключ значение
                return *f;
            }
        }
        return std::nullopt;
    }
private:
    std::map<int, std::function<void(inf::ChatChange &)>> chatCallbacks;  //хранение обсерверов для чатов
    std::optional<std::function<void(inf::ChatChange &)>> generalCallback; // для обработки чатов, о которых юзер пока не знает
    std::multimap<int, std::pair<std::shared_ptr<void>, void *>> callbacks; // для хранения различных callback
    // int - cmd различных callback
    // первый void * - контекст
    // второй void * - callback
};


#endif //NETLIB_ANNOUNCER_H
