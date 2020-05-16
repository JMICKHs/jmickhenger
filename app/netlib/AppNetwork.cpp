#include "AppNetwork.h"

using namespace std;
using namespace inf;

string getIdNameForServer(int id) {
    return "id: " + to_string(id);
}

string getAuthNameForServer(const string & nickname) {
    return "auth: " + nickname;
}

AppNet::AppNet() {
    announcer = std::make_unique<Announcer>();
    cache = unique_ptr<AbstractCache>(new Cache);
    client = Client::shared();
}

shared_ptr<AppNet> AppNet::shared() {
    static shared_ptr<AppNet> single(new AppNet);//make_shared использовать нельзя, так как нет доступного конструктора
    return single;
}

void AppNet::runClient(const function<void(int)> & errHandler) {
    client->setErrHandler(errHandler);
    if (!clientStarted) {
        clientStarted = true;
        client->run();
        setHandlers();
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


// лучше сделать фабрику body, а не делать в каждом методе
void AppNet::auth(const string &login, const string &pass, const function<void(MyAccount &, errstr &)> &callback) {
    client->write(getAuthNameForServer(login));
    Parser parser;
    parser.addStr(login, MyAccount::nameLogin);
    parser.addStr(pass, MyAccount::namePassword);
    Query query((int)Cmds::auth, parser.getRes());
    announcer->addCallback<string, inf::MyAccount &, errstr &>((int)Cmds::auth, login, callback);
    client->write(query.encode());
}

void AppNet::registration(const MyAccount &acc, const function<void(int, errstr &)> &callback) {
    client->write(getAuthNameForServer(acc.login));
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

void AppNet::getChatRoom(int idUser, int idChat, const function<void(ChatRoom &, errstr &)> &callback) {
    Parser parser;
    parser.addInt(idUser, MyAccount::nameId);
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

void AppNet::getMsgs(int idUser, int idChat, int start, int end, const function<void(vector<Message> &, errstr &)> &callback) {
    Parser parser;
    parser.addInt(idUser, MyAccount::nameId);
    parser.addInt(idChat, ChatRoom::nameId);
    parser.addInt(start, ChatRoom::nameStart);
    parser.addInt(end, ChatRoom::nameEnd);
    Query query((int)Cmds::getMessages, parser.getRes());
    announcer->addCallback<int, vector<Message> &, errstr &>((int)Cmds::getMessages, idChat, callback);
    client->write(query.encode());
}

void AppNet::getLastMsg(int idUser, int idChat, const function<void(Message &, errstr &)> &callback) {
    Parser parser;
    parser.addInt(idUser, MyAccount::nameId);
    parser.addInt(idChat, ChatRoom::nameId);
    Query query((int)Cmds::getLastMsg, parser.getRes());
    announcer->addCallback<int, Message &, errstr &>((int)Cmds::getLastMsg, idChat, callback);
    client->write(query.encode());
}


void AppNet::addFrnd(int idUser, int idFrnd, const function<void(errstr &)> &callback) {
    Parser parser;
    parser.addInt(idUser, MyAccount::nameId);
    parser.addInt(idFrnd, UserInfo::nameId);
    Query query((int)Cmds::addFrnd, parser.getRes());
    announcer->addCallback<int, errstr &>((int)Cmds::addFrnd, idFrnd, callback);
    client->write(query.encode());
}

void AppNet::getListFrnd(int id, const function<void(vector<int> &, errstr &)> &callback) {
    Parser parser;
    parser.addInt(id, MyAccount::nameId);
    Query query((int)Cmds::getListFrnd, parser.getRes());
    announcer->addCallback<int, vector<int> & , errstr &>((int)Cmds::getListFrnd, id, callback);
    client->write(query.encode());
}

void AppNet::delFrnd(int idUser, int idFrnd, const function<void(errstr &)> &callback) {
    Parser parser;
    parser.addInt(idUser, MyAccount::nameId);
    parser.addInt(idFrnd, UserInfo::nameId);
    Query query((int)Cmds::delFrnd, parser.getRes());
    announcer->addCallback<int, errstr &>((int)Cmds::delFrnd, idFrnd, callback);
    client->write(query.encode());
}

void AppNet::getInfoMe(int id, const function<void(MyAccount &, errstr &)> &callback) {
    Parser parser;
    parser.addInt(id, MyAccount::nameId);
    Query query((int)Cmds::getMe, parser.getRes());
    announcer->addCallback<int, MyAccount &, errstr &>((int)Cmds::getMe, id, callback);
    client->write(query.encode());
}

void AppNet::getUser(int myId, int idUser, const function<void(UserInfo &, errstr &)> &callback) {
    Parser parser;
    parser.addInt(myId, MyAccount::nameId);
    parser.addInt(idUser, UserInfo::nameId);
    Query query((int)Cmds::getUser, parser.getRes());
    announcer->addCallback<int, UserInfo &, errstr &>((int)Cmds::getUser, idUser, callback);
    client->write(query.encode());
}

void AppNet::createChat(const ChatRoom &room, const function<void(int, errstr &)> &callback) {
    Query query((int)Cmds::createChat, room.encode());
    announcer->addCallback<string, int, errstr &>((int)Cmds::createChat, room.name, callback);
    client->write(query.encode());
}

void AppNet::setHandlers() {
    auto self = shared_from_this();
    handlers.reserve((int)Cmds::test); // test - последняя по номеру команда
    auto f1 = [self](int cmd, errstr & err, const string & body) {
        MyAccount acc;
        acc.decode(body);
        auto f = self->announcer->getCallback<string, int, errstr &>(cmd, acc.login);
        if(!err) {
            self->client->write(getIdNameForServer(acc.id));
        }
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
        if(!err) {
            self->client->write(getIdNameForServer(acc.id));
        }
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
    auto f10 = [self](int cmd, errstr & err, const string & body) {
        Parser parser;
        parser.setJson(body);
        int id = parser.getInt(UserInfo::nameId);
        vector<int> listFrnd = parser.getArrInt(UserInfo::nameListFrnd);
        auto f = self->announcer->getCallback<int, vector<int> & , errstr &>(cmd, id);
        if (f) {
            f.value()(listFrnd, err);
        } else {
            cout << "cmd " << cmd << " " << body << " не найден callback\n";
        }
    };
    handlers[(int)Cmds::getListFrnd] = f10;
    handlers[(int)Cmds::delFrnd] = f9;
    auto f12 = [self](int cmd, errstr & err, const string & body) {
        MyAccount acc;
        acc.decode(body);
        int id = acc.id;
        auto f = self->announcer->getCallback<int, MyAccount &, errstr &>(cmd, id);
        if (f) {
            f.value()(acc, err);
        } else {
            cout << "cmd " << cmd << " " << body << " не найден callback\n";
        }
    };
    handlers[(int)Cmds::getMe] = f12;
    auto f13 = [self](int cmd, errstr & err, const string & body) {
        UserInfo user;
        user.decode(body);
        auto f = self->announcer->getCallback<int, UserInfo &, errstr &>(cmd, user.id);
        if (f) {
            f.value()(user, err);
        } else {
            cout << "cmd " << cmd << " " << body << " не найден callback\n";
        }
    };
    handlers[(int)Cmds::getUser] = f13;
    auto f14 = [self](int cmd, errstr & err, const string & body) {
        ChatRoom room;
        room.decode(body);
        auto f = self->announcer->getCallback<string, int, errstr &>(cmd, room.name);
        if (f) {
            f.value()(room.idChat, err);
        } else {
            cout << "cmd " << cmd << " " << body << " не найден callback\n";
        }
    };
    handlers[(int)Cmds::createChat] = f14;
}

optional<MyAccount> AppNet::accFromCache() {
    return nullopt;
}


