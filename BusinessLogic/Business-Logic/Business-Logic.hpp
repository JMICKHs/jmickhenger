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
    std::map<std::string, std::shared_ptr<AbstractService<DBWorker, JsonParser>>> workers;
    std::shared_ptr<Queue<ResponseStruct>> QueueOut;
    Cmds cmds;

public:
    BusinessLogic(unsigned int queueSize = 10000);
    BusinessLogic(Parser& ps, unsigned int queueSize = 10000);
    void SetRequest(std::shared_ptr<std::pair<int, std::string>> JsonStr);
    std::shared_ptr<ResponseStruct> GetResponse();
    ~BusinessLogic();
};

template<typename Parser>
BusinessLogic<Parser>::BusinessLogic(unsigned int queueSize) {
    QueueOut = std::make_shared<Queue<ResponseStruct>>(queueSize);

    workers["auth"] = std::make_shared<LoginService<DBWorker, JsonParser>>(QueueOut);
    workers["sendMsg"] = std::make_shared<SendMessageService<DBWorker, JsonParser>>(QueueOut);
    workers["friends"] = std::make_shared<FriendsService<DBWorker, JsonParser>>(QueueOut);
    workers["userInfo"] = std::make_shared<UserInfoService<DBWorker, JsonParser>>(QueueOut);
    workers["chatInfo"] = std::make_shared<GetChatInfoService<DBWorker, JsonParser>>(QueueOut);
    workers["changeMsg"] = std::make_shared<ChangeMessageService<DBWorker, JsonParser>>(QueueOut);
    workers["changeChat"] = std::make_shared<ChangeChatService<DBWorker, JsonParser>>(QueueOut);

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
BusinessLogic<Parser>::BusinessLogic(Parser &ps, unsigned int queueSize) : BusinessLogic() {
    jsp = ps;

    QueueOut = std::make_shared<Queue<ResponseStruct>>(queueSize);

    workers["auth"] = std::make_shared<LoginService<DBWorker, JsonParser>>(QueueOut);
    workers["sendMsg"] = std::make_shared<SendMessageService<DBWorker, JsonParser>>(QueueOut);
    workers["friends"] = std::make_shared<FriendsService<DBWorker, JsonParser>>(QueueOut);
    workers["userInfo"] = std::make_shared<UserInfoService<DBWorker, JsonParser>>(QueueOut);
    workers["chatInfo"] = std::make_shared<GetChatInfoService<DBWorker, JsonParser>>(QueueOut);
    workers["changeMsg"] = std::make_shared<ChangeMessageService<DBWorker, JsonParser>>(QueueOut);
    workers["changeChat"] = std::make_shared<ChangeChatService<DBWorker, JsonParser>>(QueueOut);

    for (auto&& i : workers){
        i.second->Run();
    }
}

template<typename Parser>
void BusinessLogic<Parser>::SetRequest(std::shared_ptr<std::pair<int, std::string>> JsonStr) {
    jsp.SetJson(JsonStr->second);
    int cmd = jsp.GetInt("cmd");
    if (cmd == registration || cmd == auth)
        workers["auth"]->PushRequest(*JsonStr);
    else if (cmd == sendMessage)
        workers["sendMsg"]->PushRequest(*JsonStr);
    else if (cmd == getChatRoom || cmd == getMessages || cmd == getLastMsg)
        workers["chatInfo"]->PushRequest(*JsonStr);
    else if (cmd == addFrnd || cmd == getListFrnd || cmd == delFrnd || cmd == getListChat || cmd == addFrndNick)
        workers["friends"]->PushRequest(*JsonStr);
    else if (cmd == changeUser || cmd == getUser || cmd == getMe)
        workers["userInfo"]->PushRequest(*JsonStr);
    else if (cmd == createChat || cmd == delChat || cmd == changeChat)
        workers["changeChat"]->PushRequest(*JsonStr);
    else if (cmd == changeMessage || cmd == delMessage || cmd == readChat)
        workers["changeMsg"]->PushRequest(*JsonStr);
}

template<typename Parser>
std::shared_ptr<ResponseStruct> BusinessLogic<Parser>::GetResponse() {
    return std::make_shared<ResponseStruct>(QueueOut->PopFront());
}
