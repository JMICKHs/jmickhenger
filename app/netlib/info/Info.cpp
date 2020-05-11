//
// Created by Sergei Alexeev on 05.05.2020.
//

#include "Info.h"

Codeble::Codeble() {
    parser = shared_ptr<AbstractParser>(new Parser);
}

inf::MyAccount::MyAccount()
        : id(-1), login("NIL"), pathToAvatar("NIL"), password("NIL"), chats(), friends() {}

inf::MyAccount::MyAccount(int id,
                          const string &nickname,
                          const string &image,
                          const string &pass,
                          const vector<int> & chats,
                          const vector<int> & friends)
        : id(id), login(nickname), pathToAvatar(image), password(pass), chats(chats), friends(friends) {}

string inf::MyAccount::encode() const {
    parser->clear();
    parser->addInt(id, nameId);
    parser->addStr(login, nameLogin);
    parser->addStr(password, namePassword);
    parser->addStr(pathToAvatar, namePathImage);
    parser->addArrInt(chats, nameChats);
    parser->addArrInt(friends, nameFriends);

    return parser->getRes();
}

void inf::MyAccount::decode(const string &json) {
    parser->setJson(json);
    id = parser->getInt(nameId);
    login = parser->getStr(nameLogin);
    password = parser->getStr(namePassword);
    pathToAvatar = parser->getStr(namePathImage);
    chats = parser->getArrInt(nameChats);
}

const string inf::MyAccount::nameId = "id";
const string inf::MyAccount::nameLogin = "login";
const string inf::MyAccount::namePathImage = "pathImage";
const string inf::MyAccount::namePassword = "password";
const string inf::MyAccount::nameChats = "chats";
const string inf::MyAccount::nameFriends = "friends";


inf::UserInfo::UserInfo() : id(-1), login(), pathToAvatar(){}

inf::UserInfo::UserInfo(int id, const string & login, const string & image)
    : id(id), login(login), pathToAvatar(image) {}

string inf::UserInfo::encode() const {
    parser->clear();
    parser->addInt(id, nameId);
    parser->addStr(login, nameLogin);
    parser->addStr(pathToAvatar, namePathImage);

    return parser->getRes();
}

void inf::UserInfo::decode(const string &json) {
    parser->setJson(json);
    id = parser->getInt(nameId);
    login = parser->getStr(nameLogin);
    pathToAvatar = parser->getStr(namePathImage);
}

const string inf::UserInfo::nameId = "id";
const string inf::UserInfo::nameLogin = "login";
const string inf::UserInfo::namePathImage = "pathImage";

inf::Message::Message()
    : chatId(-1), number(-1), text(), idOwner(-1), timesend(), checked(false) {}

inf::Message::Message(int id, int n, const string &text, int owner, time_t send, bool check)
    : chatId(id), number(n), text(text), idOwner(owner), timesend(send), checked(check){}

string inf::Message::encode() const {
    parser->clear();
    parser->addInt(chatId, nameId);
    parser->addInt(number, nameNumber);
    parser->addStr(text, nameText);
    parser->addInt(idOwner, nameOwner);
    parser->addInt(timesend, nameTime);
    parser->addBool(checked, nameCheck);

    return parser->getRes();
}

void inf::Message::decode(const string & json) {
    parser->setJson(json);
    chatId = parser->getInt(nameId);
    number = parser->getInt(nameNumber);
    text = parser->getStr(nameText);
    idOwner = parser->getInt(nameOwner);
    timesend = parser->getInt(nameTime);
    checked = parser->getBool(nameCheck);
}

const string inf::Message::nameId = "idChat";
const string inf::Message::nameNumber = "number";
const string inf::Message::nameText = "text";
const string inf::Message::nameOwner = "owner";
const string inf::Message::nameTime = "time";
const string inf::Message::nameCheck = "checked";

inf::ChatInfo::ChatInfo()
    : idChat(-1), name() {}

inf::ChatInfo::ChatInfo(int id, const string &name)
    : idChat(id), name(name) {}

string inf::ChatInfo::encode() const {
    parser->clear();
    parser->addInt(idChat, nameId);
    parser->addStr(name, nameChat);

    return parser->getRes();
}

void inf::ChatInfo::decode(const string & json) {
    parser->setJson(json);
    idChat = parser->getInt(nameId);
    name = parser->getStr(nameChat);
}

const string inf::ChatInfo::nameId = "id";
const string inf::ChatInfo::nameChat = "name";
const string inf::ChatInfo::nameChatList = "chatList";

bool inf::ChatInfo::operator==(const inf::ChatInfo &other) const {
    if(idChat == other.idChat && name == other.name) {
        return true;
    }
    return false;
}

inf::ChatRoom::ChatRoom() : idChat(-1) {}

inf::ChatRoom::ChatRoom(int id, const string &name, const vector<int> & users, const vector<int> & admins)
    : idChat(id), name(name), idUsers(users), idAdmins(admins){}

string inf::ChatRoom::encode() const {
    parser->clear();
    parser->addInt(idChat, nameId);
    parser->addStr(name, nameChat);
    parser->addArrInt(idUsers, nameUsers);
    parser->addArrInt(idAdmins, nameAdmins);

    return parser->getRes();
}

void inf::ChatRoom::decode(const string & json) {
    parser->setJson(json);
    idChat = parser->getInt(nameId);
    name = parser->getStr(nameChat);
    idUsers = parser->getArrInt(nameUsers);
    idAdmins = parser->getArrInt(nameAdmins);
}

const string inf::ChatRoom::nameId = "id";
const string inf::ChatRoom::nameChat = "name";
const string inf::ChatRoom::nameUsers = "users";
const string inf::ChatRoom::nameAdmins = "admins";

inf::ChatChange::ChatChange()
    : idChat(-1) {}

inf::ChatChange::ChatChange(int id, const string &cmd, const vector<inf::Message> & msgs)
    : idChat(id), action(cmd), messages(msgs) {}

string inf::ChatChange::encode() const {
    parser->clear();
    parser->addInt(idChat, nameId);
    parser->addStr(action, nameCmd);
    vector<string> tmp;
    for(const Message & item: messages) {
        tmp.push_back(item.encode());
    }
    parser->addArrCustom(tmp, nameMsg);

    return parser->getRes();
}

void inf::ChatChange::decode(const string &json) {
    parser->setJson(json);
    idChat = parser->getInt(nameId);
    action = parser->getStr(nameCmd);
    for(const auto & item : parser->getArrCustom(nameMsg)) {
        Message msg;
        msg.decode(item);
        messages.push_back(msg);
    }
}

const string inf::ChatChange::nameId = "id";
const string inf::ChatChange::nameCmd = "cmd";
const string inf::ChatChange::nameMsg = "messages";

inf::Reply::Reply() : err(), status(-1), cmd(-1), body() {}

inf::Reply::Reply(const string &ec, int stat, int cmd, const string &body)
    : err(ec), status(stat), cmd(cmd), body(body) {}

string inf::Reply::encode() const {
    parser->clear();
    parser->addStr(err, nameErr);
    parser->addInt(status, nameStatus);
    parser->addInt(cmd, nameCmd);
    parser->addCustom(body, nameBody);

    return parser->getRes();
}

void inf::Reply::decode(const string &json) {
    parser->setJson(json);
    err = parser->getStr(nameErr);
    status = parser->getInt(nameStatus);
    cmd = parser->getInt(nameCmd);
    body = parser->getCustom(nameBody);
}

const string inf::Reply::nameErr = "error";
const string inf::Reply::nameStatus = "status";
const string inf::Reply::nameCmd = "cmd";
const string inf::Reply::nameBody = "body";

inf::Query::Query() : cmd(-1), body() {}
inf::Query::Query(int command, const string & essence): cmd(command), body(essence) {}

const string inf::Query::nameCmd = "cmd";
const string inf::Query::nameBody = "body";

string inf::Query::encode() const {
    parser->clear();
    parser->addInt(cmd, nameCmd);
    parser->addCustom(body, nameBody);
    return parser->getRes();
}

void inf::Query::decode(const string &json) {
    parser->setJson(json);
    cmd = parser->getInt(nameCmd);
    body = parser->getCustom(nameBody);
}

