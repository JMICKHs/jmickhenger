//
// Created by Sergei Alexeev on 05.05.2020.
//

#include "AppNetwork.h"

optional<shared_ptr<AppNetwork>> AppNetwork::single = nullopt;

AppNetwork::AppNetwork() {
    announcer = unique_ptr<Announcer>(new Announcer);
    cache = unique_ptr<AbstractCache>(new Cache);
    client = Client::shared();
    client->run();
    client->setMsgHandler([](string msg) {
        cout << "server - " << msg;
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
