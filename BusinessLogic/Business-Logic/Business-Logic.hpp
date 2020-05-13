#pragma once

#include <map>
#include <memory>
#include <condition_variable>
#include "../JsonParser/JsonParser.h"
#include "../Services/Services.hpp"
#include "../Queue/Queue.hpp"


template <typename Parser>
class BusinessLogic
{
    Parser jsp;
    std::map<int, std::shared_ptr<AbstractService<DBWorker, JsonParser>>> workers;
    std::shared_ptr<Queue<ResponseStruct>> QueueOut;

public:
    BusinessLogic();
    BusinessLogic(Parser& ps);
    void SetRequest(const std::string& JsonStr);
    ResponseStruct GetResponse();
    ~BusinessLogic();
};

template<typename Parser>
BusinessLogic<Parser>::BusinessLogic() {
    QueueOut = std::make_shared<Queue<ResponseStruct>>();

    workers[1] = std::make_shared<NewUserService<DBWorker, JsonParser>>(QueueOut);
    workers[2] = std::make_shared<LoginService<DBWorker, JsonParser>>(QueueOut);
    workers[3] = std::make_shared<NewMessageService<DBWorker, JsonParser>>(QueueOut);
    workers[4] = std::make_shared<NewChatService<DBWorker, JsonParser>>(QueueOut);
    workers[5] = std::make_shared<LoadChatPartService<DBWorker, JsonParser>>(QueueOut);

    for (auto&& i : workers){
        i.second->Run();
    }
}

template<typename Parser>
BusinessLogic<Parser>::~BusinessLogic() {
    for (auto&& i : workers){
        i.second->Kill();
    }
}

template<typename Parser>
BusinessLogic<Parser>::BusinessLogic(Parser &ps) : BusinessLogic() {
    jsp = ps;
}

template<typename Parser>
void BusinessLogic<Parser>::SetRequest(const std::string &JsonStr) {
    jsp.SetJson(JsonStr);
    int cmd = jsp.GetInt("cmd");
    workers[cmd]->PushRequest(JsonStr);
}

template<typename Parser>
ResponseStruct BusinessLogic<Parser>::GetResponse() {
    auto tmp = QueueOut->Front();
    QueueOut->Pop();
    return tmp;
}
