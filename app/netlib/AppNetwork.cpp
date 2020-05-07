//
// Created by Sergei Alexeev on 05.05.2020.
//



#include "AppNetwork.h"

#include <memory>

optional<shared_ptr<AppNetwork>> AppNetwork::single = nullopt;

AppNetwork::AppNetwork() {
    announcer = std::make_unique<Announcer>();
    cache = unique_ptr<AbstractCache>(new Cache);
    client = Client::shared();
    client->run();
    client->setMsgHandler([](const string & msg) {
        cout << "server call me -  " << msg;
    });
    client->setErrHandler([](int errcode){
        cout << "O no! New err in connection! code - " << errcode << endl;
    });
}

shared_ptr<AppNetwork> AppNetwork::shared() {
    if(!single) {
        single = shared_ptr<AppNetwork>(new AppNetwork);
    }
    return single.value();
}

void AppNetwork::sendMessage(const Message &msg, const function<void(const bool &, optional<string> &)> &callback) {
    Reply reply("", 0, 5, msg.encode()); //временный код для отправки сообщений
    client->write(reply.encode());
}
