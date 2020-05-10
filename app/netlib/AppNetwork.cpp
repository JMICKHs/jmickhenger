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
    if (!clientStarted) {
        clientStarted = true;
        client->run();
    }
}

void AppNet::stopClient() {
    if (clientStarted) {
        clientStarted = false;
        client->close();
    }
}


void AppNet::readHandler(const string &str) {
    Package p;
    p.decode(str);
    optional<string> err;
    string body(p.body);
    if (p.err.empty()) {
        err = nullopt;
    } else {
        err = p.err;
    }
    switch (p.cmd) {
        case ((int)Cmds::sendMessage): {
            Parser parser;
            parser.setJson(body);
            int time = parser.getInt(Message::nameTime);
            auto f = announcer->getCallback<int, optional<string> &>(p.cmd, time);
            if (f) {
                f.value()(err);
            }
        }
        default: {
            cout << "неверный cmd - " << p.cmd << endl;
            break;
        }
    }
}

void AppNet::sendMsg(const Message & msg, const function<void(optional<string> &)> & callback) {
    Package p("", 0, (int)Cmds::sendMessage, msg.encode()); // временный хардкоддинг
    client->write(p.encode() + "\r\n");
    announcer->addCallback<int, optional<string> &>((int)Cmds::sendMessage, msg.timesend, callback);
    // кладем callback в multimap и при необходимом ответе сервера вызываем его
}

void AppNet::setObserverChat(int idChat, const function<void(ChatChange &)>& callback) {
    announcer->addChatCallback(idChat, callback);
}

void AppNet::setObserverUnknownChat(const function<void(ChatChange &)>& callback) {
    announcer->setChatAnonCallback(callback);
}




