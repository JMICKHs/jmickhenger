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
        client->setMsgHandler(boost::bind(&AppNet::readHandler, shared_from_this(), _1));
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
    try {
        p.decode(str);
    } catch(...) {
        cout << "server uncodeble - " << str << endl;
    }

    optional<string> err;
    string body(p.body);
    if (p.err.empty()) {
        err = nullopt;
    } else {
        err = p.err;
    }
    // надо разделить на фун
    switch (p.cmd) {
        case ((int)Cmds::registration): {
            MyAccount acc;
            acc.decode(body);
            auto f = announcer->getCallback<string, int, errstr &>(p.cmd, acc.login);
            if (f) {
                f.value()(acc.id, err);
            } else {
                cout << "cmd " << p.cmd << " " << str <<" не найден callback\n";
            }
            break;
        }
        case ((int)Cmds::auth): {
            MyAccount acc;
            acc.decode(body);
            auto f = announcer->getCallback<string, inf::MyAccount &, errstr &>(p.cmd, acc.login);
            if (f) {
                f.value()(acc, err);
            } else {
                cout << "cmd " << p.cmd << " " << str <<" не найден callback\n";
            }
            break;
        }
        case ((int)Cmds::sendMessage): {
            Message tmpMsg;
            tmpMsg.decode(body);
            int time = tmpMsg.timesend;
            auto f = announcer->getCallback<int, optional<string> &>(p.cmd, time);
            if (f) {
                f.value()(err);
            } else {
                cout << "cmd " << p.cmd << " " << str <<" не найден callback\n";
            }
            break;
        }
        default: {
            cout << "неверный cmd - " << p.cmd << " " << str << endl;
            break;
        }
    }
}

void AppNet::auth(const string &login, const string &pass, const function<void(MyAccount &, errstr &)> &callback) {
    Parser parser;
    parser.addStr(login, MyAccount::nameLogin);
    parser.addStr(pass, MyAccount::namePassword);
    Package p("", 0, (int)Cmds::auth, parser.getRes());
    client->write(p.encode());

    announcer->addCallback<string, inf::MyAccount &, errstr &>((int)Cmds::sendMessage, login, callback);

}

void AppNet::registration(const MyAccount &acc, const function<void(int, errstr &)> &callback) {
    Package p("", 0, (int)Cmds::registration, acc.encode());
    client->write(p.encode());

    announcer->addCallback<string, int, errstr &>((int)Cmds::registration, acc.login, callback);
}

void AppNet::sendMsg(const Message & msg, const function<void(optional<string> &)> & callback) {
    Package p("", 0, (int)Cmds::sendMessage, msg.encode());
    client->write(p.encode());
    announcer->addCallback<int, errstr &>((int)Cmds::sendMessage, msg.timesend, callback);
}

void AppNet::setObserverChat(int idChat, const function<void(ChatChange &)>& callback) {
    announcer->addChatCallback(idChat, callback);
}

void AppNet::setObserverUnknownChat(const function<void(ChatChange &)>& callback) {
    announcer->setChatAnonCallback(callback);
}







