#pragma once

#include <queue>
#include <string>
#include <vector>
#include <thread>
#include <sstream>
#include <memory>
#include <ctime>
#include <iostream>
#include <boost/lockfree/spsc_queue.hpp>
#include <condition_variable>
#include "../SupportStructures/SupportSructures.h"
#include "../JsonParser/JsonParser.h"
#include "../DBWorker/DBWorker.h"
#include "../Queue/Queue.hpp"
#include "KeyNames.h"


template<class DB, class Parser>
class AbstractService
{
protected:
    std::string JsonStr;
    int userId;
    Parser jsp;
    DB dbw;
    int cmd;
    std::string error;
    std::shared_ptr<Queue<ResponseStruct>> queueOut;
    Queue<std::pair<int, std::string>> queueIn;
    std::thread thread;

    virtual void parseJSON() = 0;
    virtual void dbWork() = 0;
    virtual void createResponse() = 0;
    virtual void clear() = 0;
    void createJsonStartPart(int _cmd);
    void sendIncomingMessage(int _chatId, ChatMessage _msg, std::vector<int> _participants, int _userId, std::string CMD);

public:
    AbstractService() = default;
    AbstractService(std::shared_ptr<Queue<ResponseStruct>> q);
    AbstractService(DB& database, Parser& parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    void LogicRealize();
    void PushRequest(std::pair<int, std::string> json);
    void Run();
    void Kill();
    ~AbstractService()= default;
};

template<class DB, class Parser>
class SendMessageService : public virtual AbstractService<DBWorker, JsonParser>
{
    ChatMessage msg;
    int chatId;
    std::string chatName;
    int msgNum;
    std::vector<int> participants;
    int requestTime;


    void parseJSON();
    void dbWork();
    void createResponse();
    void clear();

public:
    SendMessageService() = delete;
    SendMessageService(std::shared_ptr<Queue<ResponseStruct>> q);
    SendMessageService(DB& database, Parser& parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    ~SendMessageService();
};

template<class DB, class Parser>
class LoginService : public virtual AbstractService<DBWorker, JsonParser>
{
    std::string login;
    std::string password;
    std::string avatar;
    int incorrectId;
    bool isDataRight;
    std::vector<int> friends;
    std::vector<int> chats;

    void parseJSON();
    void dbWork();
    void createResponse();
    void clear();

public:
    LoginService() = delete;
    LoginService(std::shared_ptr<Queue<ResponseStruct>> q);
    LoginService(DB& database, Parser& parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    ~LoginService();
};

template<class DB, class Parser>
class GetChatInfoService : public virtual AbstractService<DBWorker, JsonParser> {
    int chatId;
    std::string chatName;
    int lBoard;
    int rBoard;
    int adminId;
    std::vector<ChatMessage> msgVec;
    std::vector<int> participants;
    int lastMsgOwner;
    int checkedCntr;

    void parseJSON();
    void dbWork();
    void createResponse();
    void clear();

public:
    GetChatInfoService() = delete;
    GetChatInfoService(std::shared_ptr<Queue<ResponseStruct>> q);
    GetChatInfoService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    ~GetChatInfoService();

};

template<class DB, class Parser>
class FriendsService : public virtual AbstractService<DBWorker, JsonParser>
{
    int friendId;
    std::vector<int> friendsIds;
    std::vector<int> chatIds;
    std::vector<std::string> chatNames;
    std::string login;

    void parseJSON();
    void dbWork();
    void createResponse();
    void clear();

public:
    FriendsService() = delete;
    FriendsService(std::shared_ptr<Queue<ResponseStruct>> q);
    FriendsService(DB& database, Parser& parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    ~FriendsService();
};

template<class DB, class Parser>
class UserInfoService : public virtual AbstractService<DBWorker, JsonParser>
{

    int friendId;
    std::string friendName;
    std::string friendAvatar;


    void parseJSON();
    void dbWork();
    void createResponse();
    void clear();

public:
    UserInfoService() = delete;
    UserInfoService(std::shared_ptr<Queue<ResponseStruct>> q);
    UserInfoService(DB& database, Parser& parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    ~UserInfoService();
};

template<class DB, class Parser>
class ChangeChatService : public virtual AbstractService<DBWorker, JsonParser>
{
    std::string chatName;
    int chatId;
    std::vector<int> participants;
    int adminId;
    ChatMessage msg;
    int lastMsgOwner;

    void parseJSON();
    void dbWork();
    void createResponse();
    void clear();

public:
    ChangeChatService() = delete;
    ChangeChatService(std::shared_ptr<Queue<ResponseStruct>> q);
    ChangeChatService(DB& database, Parser& parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    ~ChangeChatService() = default;
};

template<class DB, class Parser>
class ChangeMessageService : public virtual AbstractService<DBWorker, JsonParser> {
    int chatId;
    int msgNum;
    ChatMessage msg;
    std::vector<int> participants;
    bool isAllRight;
    std::vector<ChatMessage> msgVec;
    int firstMsgNum;

    void parseJSON();
    void dbWork();
    void createResponse();
    void clear();

public:
    ChangeMessageService() = delete;
    ChangeMessageService(std::shared_ptr<Queue<ResponseStruct>> q);
    ChangeMessageService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    ~ChangeMessageService() = default;
};


template<class DB, class Parser>
ChangeMessageService<DB, Parser>::ChangeMessageService(std::shared_ptr<Queue<ResponseStruct>> q) {
    queueOut = q;
    userId = -1;
    isAllRight = false;
    firstMsgNum = -1;
}

template<class DB, class Parser>
ChangeMessageService<DB, Parser>::ChangeMessageService(DB &database, Parser &parser,
                                                       std::shared_ptr<Queue<ResponseStruct>> queue) {
    jsp = parser;
    dbw = database;
    queueOut = queue;
    userId = -1;
    isAllRight = false;
    firstMsgNum = -1;
}

template<class DB, class Parser>
AbstractService<DB, Parser>::AbstractService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> queue) {
    queueOut = queue;
}

template<class DB, class Parser>
void AbstractService<DB, Parser>::Kill() {
    PushRequest(std::make_pair<int, std::string>(0, (std::string)Errors::kill));
    thread.join();
}

template<class DB, class Parser>
void AbstractService<DB, Parser>::PushRequest(std::pair<int, std::string> json) {
    queueIn.Push(json);
}

template<class DB, class Parser>
void AbstractService<DB, Parser>::Run() {
    thread = std::thread(&AbstractService<DB, Parser>::LogicRealize, std::ref(*this));
}

template<class DB, class Parser>
AbstractService<DB, Parser>::AbstractService(std::shared_ptr<Queue<ResponseStruct>> q) {
    queueOut = q;
}

template<class DB, class Parser>
void AbstractService<DB, Parser>::LogicRealize() {
    while (true) {
        auto tmp = queueIn.PopFront();
        JsonStr = tmp.second;
        userId = tmp.first;

        if (JsonStr == Errors::kill){
            break;
        }

        try {
            parseJSON();
        }
        catch (...) {
            std::cout << "Something wrong with this json: " << JsonStr << std::endl;
        }
        //try {
        dbWork();
        //}
        //catch (...) {
        //std::cout << "Something wrong with DB" << std::endl;
        //}
        try {
            createResponse();
        }
        catch (...) {
            std::cout << "Какие-то траблесы с формированием ответного Json" << std::endl << std::endl;
        }
        clear();
    }
}

template<class DB, class Parser>
void AbstractService<DB, Parser>::createJsonStartPart(int _cmd) {
    jsp.AddPairStr(JsonFieldNames::error, error);
    jsp.CreateDict(JsonFieldNames::status);
    if (error.empty()){
        jsp.AddInt(0);
    }
    else{
        jsp.AddInt(-1);
    }
    jsp.AddPairInt(JsonFieldNames::cmd, _cmd);
    jsp.MemorizePos();
}

template<class DB, class Parser>
void AbstractService<DB, Parser>::sendIncomingMessage(int _chatId, ChatMessage _msg, std::vector<int> _participants, int _userId, std::string CMD) {
    jsp.Clear();

    createJsonStartPart(incomingMsgs);
    jsp.AddPairInt(JsonValueNames::chatId, _chatId);
    jsp.AddPairStr(JsonFieldNames::cmd, CMD);
    jsp.MemorizePos();
    jsp.AddPairInt(JsonValueNames::chatId, _chatId);
    jsp.AddPairInt(JsonValueNames::msgNumber, _msg.number);
    jsp.AddPairStr(JsonValueNames::text, _msg.message);
    jsp.AddPairStr(JsonValueNames::image, _msg.image);
    jsp.AddPairInt(JsonValueNames::msgOwner, _msg.IdUser);
    jsp.AddPairInt(JsonValueNames::time, _msg.time);
    jsp.AddPairBool(JsonValueNames::isChecked, _msg.checked);
    jsp.BuildList();
    jsp.BuildList(JsonValueNames::msgs);
    jsp.ForgotPos();
    jsp.BuildList(JsonFieldNames::body);
    jsp.BuildAll();
    JsonStr = jsp.GetJson();

    auto iter = std::find_if(_participants.begin(), _participants.end(),
                             [&](int tmp) { return tmp == _userId; });
    if (iter != _participants.end()) {
        _participants.erase(iter);
    }
    for (auto &&i : _participants) {
        ResponseStruct rs1(JsonStr, i);
        if (i == *_participants.rbegin())
            rs1.ServerId = 0;
        queueOut->Push(rs1);
    }
}


template<class DB, class Parser>
void SendMessageService<DB, Parser>::parseJSON() {
    jsp.SetJson(JsonStr);
    cmd = jsp.GetInt(JsonFieldNames::cmd);
    jsp.ParseDict(JsonFieldNames::body);
    switch (cmd) {
        case 5: {
            chatId = jsp.GetInt(JsonValueNames::chatId);
            userId = jsp.GetInt(JsonValueNames::msgOwner);
            msg.IdUser = jsp.GetInt(JsonValueNames::msgOwner);
            requestTime = jsp.GetInt(JsonValueNames::time);
            msg.time = time(nullptr);
            msg.message = jsp.GetStr(JsonValueNames::text);
            msg.image = jsp.GetStr(JsonValueNames::image);
            msg.checked = jsp.GetBool(JsonValueNames::isChecked);
            break;
        }
        default:
            error = Errors::wrongCommand;
            break;
    }
    jsp.Clear();
}

template<class DB, class Parser>
void SendMessageService<DB, Parser>::dbWork() {///разнести на 2 метода!!!!!
    std::stringstream ss;
    ss << chatId;
    dbw.ChangeCollection(DBCollectionNames::chat + ss.str());
    dbw.FindInt(DBValueNames::id, 0);
    msgNum = dbw.GetInt(DBValueNames::lastMsgNumber);
    msgNum++;
    participants = dbw.GetIntVec(DBValueNames::participants);
    chatName = dbw.GetStr(DBValueNames::chatName);
    dbw.AddInt(DBValueNames::id, 0);
    dbw.AddInt(DBValueNames::lastMsgNumber, msgNum, true);
    dbw.UpdateDoc(DBCollectionNames::chat + ss.str());
    if (chatName == "SavedMessages")
        msg.checked = true;
    dbw.AddInt(DBValueNames::id, msgNum);
    dbw.AddStr(DBValueNames::msg, msg.message);
    dbw.AddInt(DBValueNames::msgOwner, msg.IdUser);
    dbw.AddInt(DBValueNames::time, msg.time);
    dbw.AddStr(DBValueNames::image, msg.image);
    dbw.AddBool(DBValueNames::isChecked, msg.checked);
    dbw.SaveDoc();
    error += dbw.GetErrors();
}

template<class DB, class Parser>
void SendMessageService<DB, Parser>::createResponse() {
    createJsonStartPart();
    jsp.AddPairInt(JsonValueNames::chatId, chatId);
    jsp.AddPairInt(JsonValueNames::msgNumber, msgNum);
    jsp.AddPairStr(JsonValueNames::text, msg.message);
    jsp.AddPairStr(JsonValueNames::image, msg.image);
    jsp.AddPairInt(JsonValueNames::msgOwner, msg.IdUser);
    jsp.AddPairInt(JsonValueNames::time, requestTime);
    jsp.AddPairBool(JsonValueNames::isChecked, msg.checked);
    jsp.BuildList(JsonFieldNames::body);
    jsp.BuildAll();
    JsonStr = jsp.GetJson();
    ResponseStruct rs(JsonStr,msg.IdUser);
    queueOut->Push(rs);

    sendIncomingMessage(chatId, msg, participants, msg.IdUser,  JsonValueNames::addMsg);
}

template<class DB, class Parser>
void SendMessageService<DB, Parser>::clear(){
    msg = ChatMessage("", "", -1, 0, false);
    chatId = -1;
    requestTime = -1;
    msgNum = -1;
    participants.clear();
    JsonStr.clear();
    cmd = -1;
    error.clear();
    jsp.Clear();
    dbw.Clear();
    chatName.clear();
}

template<class DB, class Parser>
SendMessageService<DB, Parser>::SendMessageService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> q)
{
    dbw = database;
    jsp = parser;
    queueOut = q;
    cmd = -1;
    requestTime = -1;
    msg = ChatMessage("", "", -1, 0, false);
    chatId = -1;
    msgNum = -1;
}

template<class DB, class Parser>
SendMessageService<DB, Parser>::SendMessageService(std::shared_ptr<Queue<ResponseStruct>> q){
    queueOut = q;
    cmd = -1;
    requestTime = -1;
    msg = ChatMessage("", "", -1, 0, false);
    chatId = -1;
    msgNum = -1;
}

template<class DB, class Parser>
SendMessageService<DB, Parser>::~SendMessageService() = default;


template<class DB, class Parser>
void LoginService<DB, Parser>::parseJSON() {
    jsp.SetJson(JsonStr);
    cmd = jsp.GetInt(JsonFieldNames::cmd);
    jsp.ParseDict(JsonFieldNames::body);
    login = jsp.GetStr(JsonValueNames::login);
    password = jsp.GetStr(JsonValueNames::password);
    switch (cmd) {
        case 1: {
            avatar = jsp.GetStr(JsonValueNames::avatar);
            break;
        }
        case 2: {
            break;
        }
        default:
            error = Errors::wrongCommand;
            break;
    }
    jsp.Clear();
}

template<class DB, class Parser>
void LoginService<DB, Parser>::dbWork() {
    switch (cmd) {
        case 1: {
            if (dbw.FindStr(DBValueNames::login, login)){
                error = Errors::wrongLogin;
                return;
            }
            incorrectId = userId;
            dbw.FindInt(DBValueNames::id, 0);
            userId = dbw.GetInt(DBValueNames::cntr);
            userId++;

            /// создание чата с самим собой

            dbw.ChangeCollection(DBCollectionNames::info);
            dbw.FindInt(DBValueNames::id, 0);
            int chatId = dbw.GetInt(DBValueNames::lastChatId);
            chatId++;
            dbw.AddInt(DBValueNames::id, 0);
            dbw.AddInt(DBValueNames::lastChatId, chatId, true);
            dbw.UpdateDoc(DBCollectionNames::info);

            std::stringstream ss;
            ss << chatId;
            dbw.ChangeCollection(DBCollectionNames::chat + ss.str());
            dbw.AddInt(DBValueNames::id, 0);
            dbw.AddInt(DBValueNames::chatId, chatId);
            dbw.AddStr(DBValueNames::chatName, "SavedMessages");
            dbw.AddIntVec(DBValueNames::participants, {userId});
            dbw.AddInt(DBValueNames::lastMsgNumber, 1);
            dbw.AddInt(DBValueNames::admin, userId);
            dbw.SaveDoc();

            int ttime = time(nullptr);
            ChatMessage msg = ChatMessage("Here u can save messages you need.  ©team JMICKHs", "", 1, ttime, true);
            dbw.AddInt(DBValueNames::id, 1);
            dbw.AddStr(DBValueNames::msg, msg.message);
            dbw.AddStr(DBValueNames::image, msg.image);
            dbw.AddInt(DBValueNames::msgOwner, userId);
            dbw.AddInt(DBValueNames::time, msg.time);
            dbw.AddBool(DBValueNames::isChecked, msg.checked);

            dbw.AddBool(DBValueNames::isChecked, msg.checked);
            dbw.SaveDoc();

            ///////////////////////////////

            dbw.AddInt(DBValueNames::id, 0);
            dbw.AddInt(DBValueNames::cntr, userId, true);
            dbw.UpdateDoc(DBCollectionNames::users);
            dbw.AddInt(DBValueNames::id, userId);
            dbw.AddStr(DBValueNames::login, login);
            dbw.AddStr(DBValueNames::password, password);
            dbw.AddStr(DBValueNames::avatar, avatar);
            dbw.AddIntVec(DBValueNames::friends, friends);
            chats.push_back(chatId);
            dbw.AddIntVec(DBValueNames::chatIds, chats);
            dbw.AddStrVec(DBValueNames::chatNames, {"SavedMessages"});
            dbw.SaveDoc();
            break;
        }
        case 2: {
            incorrectId = userId;
            isDataRight = false;
            isDataRight = dbw.FindStr(DBValueNames::login, login);
            if (!isDataRight){
                error = Errors::wrongData;
                return;
            }
            if (dbw.GetStr(DBValueNames::password) == password){
                userId = dbw.GetInt(DBValueNames::id);
                avatar = dbw.GetStr(DBValueNames::avatar);
                friends = dbw.GetIntVec(DBValueNames::friends);
                chats = dbw.GetIntVec(DBValueNames::chatIds);
                break;
            }
            else {
                isDataRight = false;
                error = Errors::wrongData;
                return;
            }
        }
        default:{
            error = Errors::wrongCommand;
            break;
        }
    }
    error += dbw.GetErrors();
}

template<class DB, class Parser>
void LoginService<DB, Parser>::createResponse() {
    createJsonStartPart();
    jsp.AddPairInt(JsonValueNames::userId, userId);
    jsp.AddPairStr(JsonValueNames::login, login);
    jsp.AddPairStr(JsonValueNames::password, password);
    jsp.AddPairStr(JsonValueNames::avatar, avatar);
    jsp.MemorizePos();
    jsp.AddVec(JsonValueNames::chats, chats);
    jsp.MemorizePos();
    jsp.AddVec(JsonValueNames::friends, friends);
    jsp.ForgotPos(2);
    jsp.BuildList(JsonFieldNames::body);
    jsp.BuildAll();
    JsonStr = jsp.GetJson();

    ResponseStruct rs(JsonStr, userId, incorrectId);
    queueOut->Push(rs);
}

template<class DB, class Parser>
void LoginService<DB, Parser>::clear(){
    friends.clear();
    chats.clear();
    userId = -1;
    login.clear();
    error.clear();
    password.clear();
    avatar.clear();
    isDataRight = false;
    JsonStr.clear();
    cmd = -1;
    jsp.Clear();
    dbw.Clear();
}

template<class DB, class Parser>
LoginService<DB, Parser>::LoginService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> q){
    dbw = database;
    jsp = parser;
    queueOut = q;
    userId = -1;
    cmd = -1;
}

template<class DB, class Parser>
LoginService<DB, Parser>::LoginService(std::shared_ptr<Queue<ResponseStruct>> q) {
    queueOut = q;
    dbw.ChangeCollection(DBCollectionNames::users);
    userId = -1;
    cmd = -1;
}

template<class DB, class Parser>
LoginService<DB, Parser>::~LoginService() = default;


template<class DB, class Parser>
void GetChatInfoService<DB, Parser>::parseJSON() {
    jsp.SetJson(JsonStr);
    cmd = jsp.GetInt(JsonFieldNames::cmd);
    jsp.ParseDict(JsonFieldNames::body);
    userId = jsp.GetInt(JsonValueNames::userId);
    chatId = jsp.GetInt(JsonValueNames::chatId);
    switch (cmd) {
        case 4: case 8: {
            break;
        };
        case 6: {
            lBoard = jsp.GetInt(JsonValueNames::start);
            rBoard = jsp.GetInt(JsonValueNames::end);
            break;
        }
        default:{
            error = Errors::wrongCommand;
            break;
        }
    }
    jsp.Clear();
}

template<class DB, class Parser>
void GetChatInfoService<DB, Parser>::dbWork() {
    std::stringstream ss;
    ss << chatId;
    dbw.ChangeCollection(DBCollectionNames::chat + ss.str());
    switch (cmd) {
        case 4: {
            dbw.FindInt(DBValueNames::id, 0);
            chatName = dbw.GetStr(DBValueNames::chatName);
            participants = dbw.GetIntVec(DBValueNames::participants);
            adminId = dbw.GetInt(DBValueNames::admin);
            break;
        }
        case 8:
        case 6: {
            if (lBoard == 0) {
                dbw.FindInt(DBValueNames::id, 0);
                lBoard = rBoard = dbw.GetInt(DBValueNames::lastMsgNumber);
            }
            bool isMessage = dbw.FindInt(DBValueNames::id, lBoard, rBoard);
            if (!isMessage)
                break;
            do {
                ChatMessage mes = ChatMessage(dbw.GetStr(DBValueNames::msg), dbw.GetStr(DBValueNames::image),
                                              dbw.GetInt(DBValueNames::msgOwner), dbw.GetInt(DBValueNames::time),
                                              dbw.GetBool(DBValueNames::isChecked), dbw.GetInt(DBValueNames::id)
                );
                if (!mes.checked && mes.IdUser != userId && cmd == 6) {
                    checkedCntr = msgVec.size();
                    mes.checked = true;
                }
                msgVec.push_back(mes);
            } while (dbw.NextDoc());

            if (checkedCntr >= 0) {
                dbw.AddBool(DBValueNames::isChecked, false);
                dbw.AddBool(DBValueNames::isChecked, true, true);
                dbw.UpdateDoc(DBCollectionNames::chat + ss.str());
            }
            break;
        }
    }
    error += dbw.GetErrors();
}

template<class DB, class Parser>
void GetChatInfoService<DB, Parser>::createResponse() {
    createJsonStartPart();

    switch (cmd) {
        case 4: {
            jsp.AddPairInt(JsonValueNames::chatId, chatId);
            jsp.AddPairStr(JsonValueNames::chatName, chatName);
            jsp.MemorizePos();
            jsp.AddVec(JsonValueNames::users, participants);
            jsp.MemorizePos();
            jsp.AddVec(JsonValueNames::admins, {adminId});
            jsp.ForgotPos(2);
            jsp.BuildList(JsonFieldNames::body);
            jsp.BuildAll();
            break;
        }
        case 8:
        case 6: {
            if (cmd == 6) {
                jsp.AddPairInt(JsonValueNames::chatId, chatId);
            }
            int cntr = 0;
            for (auto &&i : msgVec) {
                jsp.MemorizePos();
                jsp.AddPairInt(JsonValueNames::chatId, chatId);
                jsp.AddPairInt(JsonValueNames::msgNumber, i.number);
                jsp.AddPairStr(JsonValueNames::text, i.message);
                jsp.AddPairStr(JsonValueNames::image, i.image);
                jsp.AddPairInt(JsonValueNames::msgOwner, i.IdUser);
                jsp.AddPairInt(DBValueNames::time, i.time);
                jsp.AddPairBool(JsonValueNames::isChecked, i.checked);
                if (cmd == 6)
                    jsp.BuildList();
                cntr++;
            }
            if (cmd == 6) {
                jsp.ForgotPos(msgVec.size() - 1);
                jsp.BuildList(JsonValueNames::msgs);
            }
            jsp.ForgotPos();
            jsp.BuildList(JsonFieldNames::body);
            jsp.BuildAll();
            break;
        }
    }

    JsonStr = jsp.GetJson();

    ResponseStruct rs(JsonStr, userId, 0);
    if (cmd == 6 && checkedCntr >= 0)
        rs.ServerId = 1;
    queueOut->Push(rs);

    if (cmd == 6 && checkedCntr >= 0) {
        jsp.Clear();
        jsp.AddPairStr(JsonFieldNames::error, error);
        jsp.CreateDict(JsonFieldNames::status);
        if (error.empty()) {
            jsp.AddInt(0);
        } else {
            jsp.AddInt(-1);
        }

        jsp.AddPairInt(JsonFieldNames::cmd, incomingMsgs);
        jsp.MemorizePos();
        jsp.AddPairInt(JsonValueNames::chatId, chatId);
        jsp.AddPairStr(JsonFieldNames::cmd, JsonValueNames::readMsg);
        for (int i = checkedCntr; i < msgVec.size(); ++i) {
            jsp.MemorizePos();
            jsp.AddPairInt(JsonValueNames::chatId, chatId);
            jsp.AddPairInt(JsonValueNames::msgNumber, msgVec[i].number);
            jsp.AddPairStr(JsonValueNames::text, msgVec[i].message);
            jsp.AddPairStr(JsonValueNames::image, msgVec[i].image);
            jsp.AddPairInt(JsonValueNames::msgOwner, msgVec[i].IdUser);
            jsp.AddPairInt(JsonValueNames::time, msgVec[i].time);
            jsp.AddPairBool(JsonValueNames::isChecked, msgVec[i].checked);
            jsp.BuildList();
        }
        jsp.ForgotPos(msgVec.size() - checkedCntr - 1);
        jsp.BuildList(JsonValueNames::msgs);
        jsp.ForgotPos();
        jsp.BuildList(JsonFieldNames::body);
        jsp.BuildAll();
        JsonStr = jsp.GetJson();

        ResponseStruct rs1(JsonStr, msgVec[msgVec.size() - 1].IdUser, 0);
        queueOut->Push(rs1);
    }
}

template<class DB, class Parser>
GetChatInfoService<DB, Parser>::GetChatInfoService(std::shared_ptr<Queue<ResponseStruct>> q){
    queueOut = q;
    cmd = -1;
    checkedCntr = -1;
    chatId = -1;
    userId = -1;
    lBoard = 0;
    rBoard = 0;
}

template<class DB, class Parser>
GetChatInfoService<DB, Parser>::GetChatInfoService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> q)
{
    dbw = database;
    jsp = parser;
    queueOut = q;
    cmd = -1;
    checkedCntr = -1;
    chatId = -1;
    userId = -1;
    lBoard = 0;
    rBoard = 0;
}

template<class DB, class Parser>
void GetChatInfoService<DB, Parser>::clear() {
    cmd = -1;
    checkedCntr = -1;
    chatId = -1;
    userId = -1;
    lBoard = 0;
    rBoard = 0;
    lastMsgOwner = -1;
    participants.clear();
    chatName.clear();
    msgVec.clear();
    JsonStr.clear();
    cmd = -1;
    error.clear();
    jsp.Clear();
    dbw.Clear();
}

template<class DB, class Parser>
GetChatInfoService<DB, Parser>::~GetChatInfoService() = default;

template<class DB, class Parser>
void FriendsService<DB, Parser>::parseJSON() {
    jsp.SetJson(JsonStr);
    cmd = jsp.GetInt(JsonFieldNames::cmd);
    jsp.ParseDict(JsonFieldNames::body);
    userId = jsp.GetInt(JsonValueNames::userId);
    switch (cmd) {
        case 3:
        case 10: {
            break;
        }
        case 9:
        case 11: {
            friendId = jsp.GetInt(JsonValueNames::friendId);
            break;
        }
        case 16: {
            login = jsp.GetStr(JsonValueNames::login);
            break;
        };
        default:
            error = Errors::wrongCommand;
            break;
    }
    jsp.Clear();
}

template<class DB, class Parser>
void FriendsService<DB, Parser>::dbWork() {
    switch (cmd) {
        case 3: {
            dbw.FindInt(DBValueNames::id, userId);
            chatIds = dbw.GetIntVec(DBValueNames::chatIds);
            chatNames = dbw.GetStrVec(DBValueNames::chatNames);
            break;
        }
        case 16:
        case 9: {
            bool isUser;
            if (!login.empty()) {
                isUser = dbw.FindStr(DBValueNames::login, login);
                friendId = dbw.GetInt(DBValueNames::id);
            } else
                isUser = dbw.FindInt(DBValueNames::id, friendId);

            if (!isUser) {
                error += Errors::wrongId;
                break;
            }
            if (friendId == userId) {
                error += Errors::addFrndYourself;
                break;
            }
            friendsIds = dbw.GetIntVec(DBValueNames::friends);
            auto iter = std::find(friendsIds.begin(), friendsIds.end(), userId);
            if (iter != friendsIds.end()) {
                error += Errors::wrongFrndAdding;
                break;
            }
            friendsIds.push_back(userId);
            dbw.AddInt(DBValueNames::id, friendId);
            dbw.AddIntVec(DBValueNames::friends, friendsIds, true);
            dbw.UpdateDoc(DBCollectionNames::users);
            dbw.FindInt(DBValueNames::id, userId);
            friendsIds = dbw.GetIntVec(DBValueNames::friends);
            friendsIds.push_back(friendId);
            dbw.AddInt(DBValueNames::id, userId);
            dbw.AddIntVec(DBValueNames::friends, friendsIds, true);
            dbw.UpdateDoc(DBCollectionNames::users);
            break;
        }
        case 10: {
            dbw.FindInt(DBValueNames::id, userId);
            friendsIds = dbw.GetIntVec(DBValueNames::friends);
            break;
        }
        case 11: {
            bool isUser = dbw.FindInt(DBValueNames::id, friendId);
            if (!isUser) {
                error += Errors::wrongId;
                break;
            }
            friendsIds = dbw.GetIntVec(DBValueNames::friends);
            auto iter = std::find(friendsIds.begin(), friendsIds.end(), userId);
            if (iter == friendsIds.end()) {
                error += Errors::wrongFrndDel;
                break;
            }
            friendsIds.erase(std::remove(friendsIds.begin(), friendsIds.end(), userId));
            dbw.AddInt(DBValueNames::id, friendId);
            dbw.AddIntVec(DBValueNames::friends, friendsIds, true);
            dbw.UpdateDoc(DBCollectionNames::users);
            dbw.FindInt(DBValueNames::id, userId);
            friendsIds = dbw.GetIntVec(DBValueNames::friends);
            friendsIds.erase(std::remove(friendsIds.begin(), friendsIds.end(), friendId));
            dbw.AddInt(DBValueNames::id, userId);
            dbw.AddIntVec(DBValueNames::friends, friendsIds, true);
            dbw.UpdateDoc(DBCollectionNames::users);
            break;
        }
    }
    error += dbw.GetErrors();
}

template<class DB, class Parser>
void FriendsService<DB, Parser>::createResponse() {
    createJsonStartPart();

    switch (cmd) {
        case 3: {
            jsp.AddPairInt(JsonValueNames::userId, userId);
            jsp.MemorizePos();

            for (int i = 0; i < chatNames.size(); ++i) {
                jsp.AddPairInt(JsonValueNames::chatId, chatIds[i]);
                jsp.AddPairStr(JsonValueNames::chatName, chatNames[i]);
                jsp.BuildList();
                jsp.MemorizePos();
            }
            jsp.ForgotPos(chatNames.size());

            jsp.BuildList(JsonValueNames::chatList);
            jsp.ForgotPos();
            break;
        }
        case 9:
        case 11: {
            jsp.AddPairInt(JsonValueNames::friendId, friendId);
            break;
        }
        case 10: {
            jsp.AddPairInt(JsonValueNames::friendId, userId);
            jsp.MemorizePos();
            jsp.AddVec(JsonValueNames::frnds, friendsIds);
            jsp.ForgotPos();
            break;
        }
        case 16: {
            jsp.AddPairStr(JsonValueNames::login, login);
            jsp.AddPairInt(JsonValueNames::friendId, friendId);
            break;
        }
    }
    jsp.BuildList(JsonFieldNames::body);
    jsp.BuildAll();
    JsonStr = jsp.GetJson();

    ResponseStruct rs(JsonStr, userId, 0);
    queueOut->Push(rs);
}

template<class DB, class Parser>
FriendsService<DB, Parser>::FriendsService(std::shared_ptr<Queue<ResponseStruct>> q){
    queueOut = q;
    dbw.ChangeCollection(DBCollectionNames::users);
    userId = -1;
    friendId = -1;
}

template<class DB, class Parser>
FriendsService<DB, Parser>::FriendsService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> q)
{
    dbw.ChangeCollection(DBCollectionNames::users);
    dbw = database;
    jsp = parser;
    queueOut = q;
    userId = -1;
    friendId = -1;
}

template<class DB, class Parser>
void FriendsService<DB, Parser>::clear() {
    userId = -1;
    friendId = -1;
    login.clear();
    friendsIds.clear();
    chatIds.clear();
    chatNames.clear();
    JsonStr.clear();
    cmd = -1;
    error.clear();
    jsp.Clear();
    dbw.Clear();
}

template<class DB, class Parser>
FriendsService<DB, Parser>::~FriendsService() = default;



template<class DB, class Parser>
void UserInfoService<DB, Parser>::parseJSON() {
    jsp.SetJson(JsonStr);
    cmd = jsp.GetInt(JsonFieldNames::cmd);
    jsp.ParseDict(JsonFieldNames::body);
    switch (cmd) {
        case 13: {
            userId = jsp.GetInt(JsonValueNames::userId);
            friendId = jsp.GetInt(JsonValueNames::friendId);
            break;
        }
        case 12: {
            userId = jsp.GetInt(JsonValueNames::userId);
            break;
        }
        default: {
            error = Errors::wrongCommand;
            break;
        }
    }
    jsp.Clear();
}

template<class DB, class Parser>
void UserInfoService<DB, Parser>::dbWork() {
    switch (cmd) {
        case 13: {
            dbw.FindInt(DBValueNames::id, friendId);
            friendName = dbw.GetStr(DBValueNames::login);
            friendAvatar = dbw.GetStr(DBValueNames::avatar);
            break;
        }
        case 12: {
            dbw.FindInt(DBValueNames::id, userId);
            JsonStr = dbw.GetJson();
            break;
        }
    }
    error += dbw.GetErrors();
}

template<class DB, class Parser>
void UserInfoService<DB, Parser>::createResponse() {
    createJsonStartPart();
    switch (cmd) {
        case 13: {
            jsp.AddPairInt(JsonValueNames::friendId, friendId);
            jsp.AddPairStr(JsonValueNames::login, friendName);
            jsp.AddPairStr(JsonValueNames::avatar, friendAvatar);
            break;
        }
        case 12: {
            jsp.AddStr(JsonStr);
            break;
        }
    }
    jsp.BuildList(JsonFieldNames::body);
    jsp.BuildAll();
    JsonStr = jsp.GetJson();

    ResponseStruct rs(JsonStr, userId, 0);
    queueOut->Push(rs);
}

template<class DB, class Parser>
UserInfoService<DB, Parser>::UserInfoService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> q)
{
    queueOut = q;
    dbw = database;
    jsp = parser;
    userId = -1;
    friendId = -1;
    cmd = -1;
}

template<class DB, class Parser>
UserInfoService<DB, Parser>::UserInfoService(std::shared_ptr<Queue<ResponseStruct>> q){
    queueOut = q;
    dbw.ChangeCollection(DBCollectionNames::users);
    userId = -1;
    friendId = -1;
    cmd = -1;
}

template<class DB, class Parser>
void UserInfoService<DB, Parser>::clear() {
    userId = -1;
    friendId = -1;
    friendAvatar.clear();
    friendName.clear();
    JsonStr.clear();
    cmd = -1;
    error.clear();
    jsp.Clear();
    dbw.Clear();
}

template<class DB, class Parser>
UserInfoService<DB, Parser>::~UserInfoService() = default;


template<class DB, class Parser>
ChangeChatService<DB, Parser>::ChangeChatService(std::shared_ptr<Queue<ResponseStruct>> q) {
    queueOut = q;
    cmd = -1;
    msg = ChatMessage();
    adminId = -1;
}

template<class DB, class Parser>
ChangeChatService<DB, Parser>::ChangeChatService(DB &database, Parser &parser,
                                                 std::shared_ptr<Queue<ResponseStruct>> queue) {
    dbw = database;
    jsp = parser;
    queueOut = queue;
    cmd = -1;
    msg = ChatMessage();
    adminId = -1;
}

template<class DB, class Parser>
void ChangeChatService<DB, Parser>::parseJSON() {
    jsp.SetJson(JsonStr);
    cmd = jsp.GetInt(JsonFieldNames::cmd);
    jsp.ParseDict(JsonFieldNames::body);
    switch (cmd) {
        case 14: {
            chatName = jsp.GetStr(JsonValueNames::chatName);
            jsp.ParseDict(JsonValueNames::users);
            participants = jsp.GetIntVec();
            std::vector<int> tmp;
            jsp.JumpToPos();
            jsp.ParseDict(JsonValueNames::admins);
            tmp = jsp.GetIntVec();
            adminId = tmp.front();
            break;
        }
        case 15: {
            userId = jsp.GetInt(JsonValueNames::userId);
            chatId = jsp.GetInt(JsonValueNames::chatId);
        }
        default:
            error = Errors::wrongCommand;
            break;
    }
    jsp.Clear();
}

template<class DB, class Parser>
void ChangeChatService<DB, Parser>::dbWork() {
    switch (cmd) {
        case 14: {
            dbw.ChangeCollection(DBCollectionNames::info);
            dbw.FindInt(DBValueNames::id, 0);
            chatId = dbw.GetInt(DBValueNames::lastChatId);
            chatId++;
            dbw.AddInt(DBValueNames::id, 0);
            dbw.AddInt(DBValueNames::lastChatId, chatId, true);
            dbw.UpdateDoc(DBCollectionNames::info);

            dbw.ChangeCollection(DBCollectionNames::users);
            for (auto&& i : participants) {
                dbw.FindInt(DBValueNames::id, i);
                std::vector<int> tmpInt = dbw.GetIntVec(DBValueNames::chatIds);
                tmpInt.push_back(chatId);
                std::vector<std::string> tmpStr = dbw.GetStrVec(DBValueNames::chatNames);
                tmpStr.push_back(chatName);
                dbw.AddInt(DBValueNames::id, i);
                dbw.AddIntVec(DBValueNames::chatIds, tmpInt, true);
                dbw.AddStrVec(DBValueNames::chatNames, tmpStr, true);
                dbw.UpdateDoc(DBCollectionNames::users);
            }

            std::stringstream ss;
            ss << chatId;
            dbw.ChangeCollection(DBCollectionNames::chat + ss.str());
            dbw.AddInt(DBValueNames::id, 0);
            dbw.AddInt(DBValueNames::chatId, chatId);
            dbw.AddStr(DBValueNames::chatName, chatName);
            dbw.AddIntVec(DBValueNames::participants, participants);
            dbw.AddInt(DBValueNames::lastMsgNumber, 1);
            dbw.AddInt(DBValueNames::admin, adminId);
            dbw.SaveDoc();

            int ttime = time(nullptr);
            msg = ChatMessage("Hello everyone! I've created new chat!", "", adminId, ttime, false);
            dbw.AddInt(DBValueNames::id, 1);
            dbw.AddStr(DBValueNames::msg, msg.message);
            dbw.AddStr(DBValueNames::image, msg.image);
            dbw.AddInt(DBValueNames::msgOwner, adminId);
            dbw.AddInt(DBValueNames::time, msg.time);
            dbw.AddBool(DBValueNames::isChecked, msg.checked);

            dbw.AddBool(DBValueNames::isChecked, msg.checked);
            dbw.SaveDoc();
            break;
        }
        case 15: {
            std::stringstream ss;
            ss << chatId;
            dbw.ChangeCollection(DBCollectionNames::chat + ss.str());
            bool isChat = dbw.FindInt(DBValueNames::id, 0);
            if (!isChat) {
                error += Errors::wrongChat;
                break;
            }
            participants = dbw.GetIntVec(DBValueNames::participants);
            adminId = dbw.GetInt(DBValueNames::admin);
            if (adminId != userId) {
                error += Errors::acsessError;
                break;
            }
            dbw.DeleteCollect(DBCollectionNames::chat + ss.str());
            break;
        }
    }
    error += dbw.GetErrors();
}

template<class DB, class Parser>
void ChangeChatService<DB, Parser>::createResponse() {
    createJsonStartPart();
    jsp.AddPairInt(JsonValueNames::chatId, chatId);

    switch (cmd) {
        case 14: {

            jsp.AddPairStr(JsonValueNames::chatName, chatName);
            jsp.MemorizePos();
            jsp.AddVec(JsonValueNames::users, participants);
            jsp.MemorizePos();
            jsp.AddVec(JsonValueNames::admins, std::vector<int>{adminId});
            jsp.ForgotPos(2);
            jsp.BuildList(JsonFieldNames::body);
            jsp.BuildAll();
            JsonStr = jsp.GetJson();

            ResponseStruct rs(JsonStr, adminId);
            queueOut->Push(rs);
            break;
        }
        case 15: {
            jsp.BuildAll();
            JsonStr = jsp.GetJson();

            ResponseStruct rs(JsonStr, adminId);
            queueOut->Push(rs);

            jsp.Clear();
            if (!error.empty())
                return;
            break;
        }
    }

    if (cmd == 14)
        sendIncomingMessage(chatId, msg, participants, adminId, JsonValueNames::addChat);
    else if (cmd == 15)
        sendIncomingMessage(chatId, msg, participants, adminId, JsonValueNames::delChat);
}

template<class DB, class Parser>
void ChangeChatService<DB, Parser>::clear() {
    msg = ChatMessage();
    lastMsgOwner = -1;
    adminId = -1;
    participants.clear();
    chatName.clear();
    JsonStr.clear();
    cmd = -1;
    error.clear();
    jsp.Clear();
    dbw.Clear();
}


template<class DB, class Parser>
void ChangeMessageService<DB, Parser>::parseJSON() {
    jsp.SetJson(JsonStr);
    cmd = jsp.GetInt(JsonFieldNames::cmd);
    jsp.ParseDict(JsonFieldNames::body);
    switch (cmd) {
        case 18: {
            chatId = jsp.GetInt(JsonValueNames::chatId);
            msg.number = jsp.GetInt(JsonValueNames::msgNumber);
            msg.message = jsp.GetStr(JsonValueNames::text);
            msg.image = jsp.GetStr(JsonValueNames::image);
            msg.IdUser = jsp.GetInt(JsonValueNames::msgOwner);
            msg.time = jsp.GetInt(JsonValueNames::time);
            msg.checked = jsp.GetBool(JsonValueNames::isChecked);
            break;
        }
        case 19: {
            userId = jsp.GetInt(JsonValueNames::userId);
            chatId = jsp.GetInt(JsonValueNames::chatId);
            msg.number = jsp.GetInt(JsonValueNames::msgNumber);
            break;
        }
        case 21: {
            userId = jsp.GetInt(JsonValueNames::userId);
            chatId = jsp.GetInt(JsonValueNames::chatId);
            break;
        }
        default: {
            error = Errors::wrongCommand;
            break;
        }
    }
    jsp.Clear();
}

template<class DB, class Parser>
void ChangeMessageService<DB, Parser>::dbWork() {
    std::stringstream ss;
    ss << chatId;
    dbw.ChangeCollection(DBCollectionNames::chat + ss.str());

    switch (cmd) {
        case 19: {
            isAllRight = dbw.FindInt(DBValueNames::id, 0);
            if (!isAllRight) {
                error += Errors::wrongChat;
                return;
            }
            if (msg.number == 1){
                error += Errors::acsessError;
                return;
            }
            int adminId = dbw.GetInt(DBValueNames::admin);
            participants = dbw.GetIntVec(DBValueNames::participants);
            isAllRight = dbw.FindInt(DBValueNames::id, msg.number);
            if (!isAllRight) {
                error += Errors::wrongId;
                return;
            }
            msg.checked = dbw.GetBool(DBValueNames::isChecked);
            msg.image = dbw.GetStr(DBValueNames::image);
            msg.time = dbw.GetInt(DBValueNames::time);
            msg.message = dbw.GetStr(DBValueNames::msg);
            dbw.AddInt(DBValueNames::id, msg.number);
            dbw.DeleteDoc(DBCollectionNames::chat + ss.str());
            break;
        }
        case 18: {
            isAllRight = dbw.FindInt(DBValueNames::id, 0);
            if (!isAllRight) {
                error += Errors::wrongChat;
                return;
            }
            if (msgNum == 1) {
                error += Errors::acsessError;
                return;
            }
            participants = dbw.GetIntVec(DBValueNames::participants);
            isAllRight = dbw.FindInt(DBValueNames::id, msg.number);
            if (!isAllRight) {
                error += Errors::wrongId;
                return;
            }
            dbw.AddInt(DBValueNames::id, msg.number);
            dbw.AddStr(DBValueNames::msg, msg.message, true);
            dbw.UpdateDoc(DBCollectionNames::chat + ss.str());
            break;
        }
        case 21: {
            isAllRight = dbw.FindBool(DBValueNames::isChecked, false);
            if (isAllRight) {
                dbw.AddBool(DBValueNames::isChecked, false);
                dbw.AddBool(DBValueNames::isChecked, true, true);
                dbw.UpdateDoc(DBCollectionNames::chat + ss.str());
                int msgWriter = dbw.GetInt(DBValueNames::msgOwner);
                if (msgWriter == userId) {
                    isAllRight = false;
                    break;
                }
                do {
                    msgVec.emplace_back(ChatMessage(
                            dbw.GetStr(DBValueNames::msg),
                            dbw.GetStr(DBValueNames::image),
                            dbw.GetInt(DBValueNames::msgOwner),
                            dbw.GetInt(DBValueNames::time),
                            true,
                            dbw.GetInt(DBValueNames::id)
                    ));
                } while (dbw.NextDoc());
            }
            break;
        }
    }

    error += dbw.GetErrors();
}

template<class DB, class Parser>
void ChangeMessageService<DB, Parser>::createResponse() {
    createJsonStartPart();
    switch (cmd) {
        case 18: {
            jsp.AddPairInt(JsonValueNames::chatId, chatId);
            jsp.AddPairInt(JsonValueNames::msgNumber, msg.number);
            jsp.AddPairStr(JsonValueNames::text, msg.message);
            jsp.AddPairStr(JsonValueNames::image, msg.image);
            jsp.AddPairInt(JsonValueNames::msgOwner, msg.IdUser);
            jsp.AddPairInt(JsonValueNames::time, msg.time);
            jsp.AddPairBool(JsonValueNames::isChecked, msg.checked);
            jsp.BuildList(JsonFieldNames::body);
            jsp.BuildAll();
            JsonStr = jsp.GetJson();
            int tmpServerCommand = 0;
            if (error.empty())
                tmpServerCommand = 1;/// тут неважно что будет за число, главное, чтобы оно было больше 0, чтобы известить сервер, что это не последний ответ
            ResponseStruct rs(JsonStr, msg.IdUser, tmpServerCommand);
            queueOut->Push(rs);

            if (error.empty()) {
                sendIncomingMessage(chatId, msg, participants, userId, JsonValueNames::changeMsg);
            }
            break;
        }
        case 19: {
            jsp.AddPairInt(JsonValueNames::chatId, chatId);
            jsp.AddPairInt(JsonValueNames::msgNumber, msg.number);
            jsp.BuildList(JsonFieldNames::body);
            jsp.BuildAll();
            JsonStr = jsp.GetJson();
            int tmpServerCommand = 0;
            if (error.empty())
                tmpServerCommand = 1;
            ResponseStruct rs(JsonStr, msg.IdUser, tmpServerCommand);
            queueOut->Push(rs);

            if (error.empty()) {
                sendIncomingMessage(chatId, msg, participants, userId, JsonValueNames::delMsg);
            }
            break;
        }
        case 21: {
            jsp.AddPairInt(JsonValueNames::chatId, chatId);
            jsp.BuildList(JsonFieldNames::body);
            jsp.BuildAll();
            JsonStr = jsp.GetJson();
            ResponseStruct rs(JsonStr, userId, 0);
            if (isAllRight)
                rs.ServerId = 1;
            queueOut->Push(rs);

            if (isAllRight) {
                jsp.AddPairStr(JsonFieldNames::error, error);
                jsp.CreateDict(JsonFieldNames::status);
                if (error.empty()) {
                    jsp.AddInt(0);
                } else {
                    jsp.AddInt(-1);
                }
                jsp.AddPairInt(JsonFieldNames::cmd, incomingMsgs);
                jsp.MemorizePos();
                jsp.AddPairInt(JsonValueNames::chatId, chatId);
                jsp.AddPairStr(JsonFieldNames::cmd, JsonValueNames::readMsg);
                for (int i = 0; i < msgVec.size(); ++i) {
                    jsp.MemorizePos();
                    jsp.AddPairInt(JsonValueNames::chatId, chatId);
                    jsp.AddPairInt(JsonValueNames::msgNumber, msgVec[i].number);
                    jsp.AddPairStr(JsonValueNames::text, msgVec[i].message);
                    jsp.AddPairStr(JsonValueNames::image, msgVec[i].image);
                    jsp.AddPairInt(JsonValueNames::msgOwner, msgVec[i].IdUser);
                    jsp.AddPairInt(JsonValueNames::time, msgVec[i].time);
                    jsp.AddPairBool(JsonValueNames::isChecked, msgVec[i].checked);
                    jsp.BuildList();
                }
                jsp.ForgotPos(msgVec.size() - 1);
                jsp.BuildList(JsonValueNames::msgs);
                jsp.ForgotPos();
                jsp.BuildList(JsonFieldNames::body);
                jsp.BuildAll();
                JsonStr = jsp.GetJson();
                ResponseStruct rs1(JsonStr, msgVec[0].IdUser, 0);
                queueOut->Push(rs1);
            }
            break;
        }
    }
}

template<class DB, class Parser>
void ChangeMessageService<DB, Parser>::clear() {
    msg = ChatMessage();
    userId = -1;
    isAllRight = false;
    participants.clear();
    JsonStr.clear();
    cmd = -1;
    error.clear();
    jsp.Clear();
    dbw.Clear();
    msgVec.clear();
    firstMsgNum = -1;
}
