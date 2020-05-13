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
        setHandlers();
//        client->write("app");
    }
}

void AppNet::stopClient() {
    if (clientStarted) {
        clientStarted = false;
        client->close();
    }
}


void AppNet::readHandler(const string &str) {
    Reply reply;

    try {
        reply.decode(str);
    } catch(...) {
        cout << str << endl;
        cout << "server uncodeble" << endl;
        return;
    }

    optional<string> err;
    string body(reply.body);
    if (reply.err.empty()) {
        err = nullopt;
    } else {
        err = reply.err;
    }


    if(handlers.count(reply.cmd)) {
        handlers[reply.cmd](reply.cmd, err, body);
    } else {
        cout << "err cmd - " << reply.cmd << endl;
    }
}

// query
//{
//  "cmd": "1",
//  "body": {
//      "login": "testLogin",
//      "password": "hwahjdssfjg"
//  }
//}
// reply
//{
//  "error": "",
//  "status": "0",
//  "cmd": "1",
//  "body": {
//      "id": "-1",
//      "login": "NIL",
//      "password": "NIL",
//      "pathImage": "NIL",
//      "chats": [],
//      "friends": []
//  }
//}
void AppNet::auth(const string &login, const string &pass, const function<void(MyAccount &, errstr &)> &callback) {
    Parser parser;
    parser.addStr(login, MyAccount::nameLogin);
    parser.addStr(pass, MyAccount::namePassword);
    Query query((int)Cmds::auth, parser.getRes());
    announcer->addCallback<string, inf::MyAccount &, errstr &>((int)Cmds::auth, login, callback);
    client->write(query.encode());
}

void AppNet::registration(const MyAccount &acc, const function<void(int, errstr &)> &callback) {
    Query query((int)Cmds::registration, acc.encode());
    announcer->addCallback<string, int, errstr &>((int)Cmds::registration, acc.login, callback);
    client->write(query.encode());
}

void AppNet::sendMsg(const Message & msg, const function<void(optional<string> &)> & callback) {
    Query query((int)Cmds::sendMessage, msg.encode());
    announcer->addCallback<int, errstr &>((int)Cmds::sendMessage, msg.timesend, callback);
    client->write(query.encode());
}

void AppNet::getListChat(int idUser, const function<void(vector<ChatInfo> &, errstr &)> &callback) {
    Parser parser;
    parser.addInt(idUser, MyAccount::nameId);
    Query query((int)Cmds::getListChat, parser.getRes());
    announcer->addCallback<int, vector<ChatInfo> &, errstr &>((int)Cmds::getListChat, idUser, callback);
    client->write(query.encode());
}

void AppNet::getChatRoom(int idChat, const function<void(ChatRoom &, errstr &)> &callback) {
    Parser parser;
    parser.addInt(idChat, ChatInfo::nameId);
    Query query((int)Cmds::getChatRoom, parser.getRes());
    announcer->addCallback<int, ChatRoom &, errstr &>((int)Cmds::getChatRoom, idChat, callback);
    client->write(query.encode());
}

void AppNet::setObserverChat(int idChat, const function<void(ChatChange &)>& callback) {
    announcer->addChatCallback(idChat, callback);
}

void AppNet::setObserverUnknownChat(const function<void(ChatChange &)>& callback) {
    announcer->setChatAnonCallback(callback);
}

void AppNet::getMsgs(int idChat, int start, int end, const function<void(vector<Message> &, errstr &)> &callback) {
    Parser parser;
    parser.addInt(idChat, ChatRoom::nameId);
    parser.addInt(start, ChatRoom::nameStart);
    parser.addInt(end, ChatRoom::nameEnd);
    Query query((int)Cmds::getMessages, parser.getRes());
    announcer->addCallback<int, vector<Message> &, errstr &>((int)Cmds::getMessages, idChat, callback);
    client->write(query.encode());
}


//query
//{
//"cmd": "8",
//"body": {
//"id": "6"
//}
//}
//reply
//{
//    "error": "",
//    "status": "0",
//    "cmd": "8",
//    "body": {
//        "idChat": "-1",
//        "number": "-1",
//        "text": "",
//        "owner": "-1",
//        "time": "0",
//        "checked": "false"
//    }
//}

void AppNet::getLastMsg(int idChat, const function<void(Message &, errstr &)> &callback) {
    Parser parser;
    parser.addInt(idChat, ChatRoom::nameId);
    Query query((int)Cmds::getLastMsg, parser.getRes());
    announcer->addCallback<int, Message &, errstr &>((int)Cmds::getLastMsg, idChat, callback);
    client->write(query.encode());
}


void AppNet::addFrnd(int idFrnd, const function<void(errstr &)> &callback) {
    Parser parser;
    parser.addInt(idFrnd, UserInfo::nameId);
    Query query((int)Cmds::getLastMsg, parser.getRes());
    announcer->addCallback<int, errstr &>((int)Cmds::addFrnd, idFrnd, callback);
    client->write(query.encode());
}


void AppNet::setHandlers() {
    auto self = shared_from_this();
    handlers.reserve((int)Cmds::test); // test - последняя по номеру команда
    auto f1 = [self](int cmd, errstr & err, const string & body) {
        MyAccount acc;
        acc.decode(body);
        auto f = self->announcer->getCallback<string, int, errstr &>(cmd, acc.login);
        if (f) {
            f.value()(acc.id, err);
        } else {
            cout << "cmd " << cmd << " " << body << " не найден callback\n";
        }
    };
    handlers[(int)Cmds::registration] = f1;
    auto f2 = [self](int cmd, errstr & err, const string & body) {
        MyAccount acc;
        acc.decode(body);
        auto f = self->announcer->getCallback<string, inf::MyAccount &, errstr &>(cmd, acc.login);
        if (f) {
            f.value()(acc, err);
        } else {
            cout << "cmd " << cmd << " " << body << " не найден callback\n";
        }
    };
    handlers[(int)Cmds::auth] = f2;
    auto f3 = [self](int cmd, errstr & err, const string & body) {
        Parser parser;
        parser.setJson(body);
        int id = parser.getInt(MyAccount::nameId);
        vector<string> tmp = parser.getArrCustom(ChatInfo::nameChatList);
        vector<ChatInfo> res; res.reserve(tmp.size());
        for(const auto & item: tmp) {
            ChatInfo info;
            info.decode(item);
            res.push_back(info);
        }
        auto f = self->announcer->getCallback<int, vector<ChatInfo> &, errstr &>(cmd, id);
        if (f) {
            f.value()(res, err);
        } else {
            cout << "cmd " << cmd << " " << body << " не найден callback\n";
        }
    };
    handlers[(int)Cmds::getListChat] = f3;
    auto f4 = [self](int cmd, errstr & err, const string & body) {
        ChatRoom room;
        room.decode(body);
        auto f = self->announcer->getCallback<int, ChatRoom&, errstr&>(cmd, room.idChat);
        if (f) {
            f.value()(room, err);
        } else {
            cout << "cmd " << cmd << " " << body << " не найден callback\n";
        }
    };
    handlers[(int)Cmds::getChatRoom] = f4;
    auto f5 = [self](int cmd, errstr & err, const string & body) {
        Message tmpMsg;
        tmpMsg.decode(body);
        int time = tmpMsg.timesend;
        auto f = self->announcer->getCallback<int, optional<string> &>(cmd, time);
        if (f) {
            f.value()(err);
        } else {
            cout << "cmd " << cmd << " " << body << " не найден callback\n";
        }
    };
    handlers[(int)Cmds::sendMessage] = f5;
    auto f6 = [self](int cmd, errstr & err, const string & body) {
        Parser parser;
        parser.setJson(body);
        int id = parser.getInt(ChatRoom::nameId);
        vector<string> tmp = parser.getArrCustom(Message::nameArr);
        vector<Message> res;
        res.reserve(tmp.size());
        for(const auto & item: tmp) {
            Message msg;
            msg.decode(item);
            res.push_back(msg);
        }
        auto f = self->announcer->getCallback<int, vector<Message> &, optional<string> &>(cmd, id);
        if (f) {
            f.value()(res, err);
        } else {
            cout << "cmd " << cmd << " " << body << " не найден callback\n";
        }
    };
    handlers[(int)Cmds::getMessages] = f6;
    auto f7 = [self](int cmd, errstr & err, const string & body) {
        ChatChange change;
        change.decode(body);
        self->announcer->notifyChat(change);
    };
    handlers[(int)Cmds::incomingMsgs] = f7;
    auto f8 = [self](int cmd, errstr & err, const string & body) {
        Message tmpMsg;
        tmpMsg.decode(body);
        auto f = self->announcer->getCallback<int, Message &, optional<string> &>(cmd, tmpMsg.chatId);
        if (f) {
            f.value()(tmpMsg, err);
        } else {
            cout << "cmd " << cmd << " " << body << " не найден callback\n";
        }
    };
    handlers[(int)Cmds::getLastMsg] = f8;
    auto f9 = [self](int cmd, errstr & err, const string & body) {
        Parser parser;
        parser.setJson(body);
        auto f = self->announcer->getCallback<int, optional<string> &>(cmd, parser.getInt(UserInfo::nameId));
        if (f) {
            f.value()(err);
        } else {
            cout << "cmd " << cmd << " " << body << " не найден callback\n";
        }
    };
    handlers[(int)Cmds::addFrnd] = f9;
}

