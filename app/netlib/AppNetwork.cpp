//
// Created by Sergei Alexeev on 05.05.2020.
//



#include "AppNetwork.h"

std::mutex AppNet::mtx = std::mutex();

optional<shared_ptr<AppNet>> AppNet::single = nullopt;

AppNet::AppNet() {
    announcer = std::make_unique<Announcer>();
    cache = unique_ptr<AbstractCache>(new Cache);
    client = Client::shared();

    client->setMsgHandler([](const string & msg) { // для проверки
        cout << "server call me -  " << msg;
    });
}

shared_ptr<AppNet> AppNet::shared() {
    if(!single) {
        mtx.lock();
        if (!single) {
            single = shared_ptr<AppNet>(new AppNet);
        }
        mtx.unlock();
    }
    return single.value();
}

void AppNet::runClient(const function<void(int)> & errHandler) {
    client->setErrHandler(errHandler);
    client->run();
}

void AppNet::stopClient() {
    client->close();
}

void AppNet::sendMsg(const Message & msg, const function<void(const bool &, optional<string> &)> & callback) {
    Package p("", 0, 5, msg.encode()); // временный хардкоддинг
    client->write(p.encode() + "\r\n");
    // кладем callback в multimap и при необходимом ответе сервера вызываем его
}

void AppNet::setObserverChat(int idChat, const function<void(const ChatChange &)>& callback) {
    announcer->addCallback(idChat, callback);
}

void AppNet::setObserverUnknownChat(const function<void(const ChatChange &)>& callback) {
    announcer->setGeneralCallback(callback);
}


