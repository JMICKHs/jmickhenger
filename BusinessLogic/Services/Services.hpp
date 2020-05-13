#pragma once

#include <queue>
#include <string>
#include <vector>
#include <thread>
#include <sstream>
#include <memory>
#include "../SupportStructures/SupportSructures.h"
#include "../JsonParser/JsonParser.h"
#include "../DBWorker/DBWorker.h"
#include "../Queue/Queue.hpp"


template<class DB, class Parser>
class AbstractService
{
protected:
    std::string JsonStr;
    Parser jsp;
    DB dbw;
    std::shared_ptr<Queue<ResponseStruct>> queueOut;
    Queue<std::string> queueIn;
    std::thread thread;
    std::condition_variable bell;

    void parseJSON() {};
    void dbWork() {};
    void createResponse() {};

public:
    AbstractService() = delete;
    AbstractService(std::shared_ptr<Queue<ResponseStruct>> q);
    AbstractService(DB& database, Parser& parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    void LogicRealize(){};
    void DoLogic();
    void PushRequest(std::string json);
    void Run();
    void Kill();
    ~AbstractService()= default;
};

template<class DB, class Parser>
class NewUserService : public virtual AbstractService<DBWorker, JsonParser>
{
    std::string login;
    std::string password;
    std::string avatar_path;

    void parseJSON();
    void dbWork();
    void createResponse();

public:
    NewUserService() = delete;
    NewUserService(std::shared_ptr<Queue<ResponseStruct>> q);
    NewUserService(DB& database, Parser& parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    ~NewUserService();
};

template<class DB, class Parser>
class LoginService : public virtual AbstractService<DBWorker, JsonParser>
{
    std::string login;
    std::string password;
    bool isDataRight;

    void parseJSON();
    void dbWork();
    void createResponse();

public:
    LoginService() = delete;
    LoginService(std::shared_ptr<Queue<ResponseStruct>> q);
    LoginService(DB& database, Parser& parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    ~LoginService();
};

template<class DB, class Parser>
class LoadChatPartService : public virtual AbstractService<DBWorker, JsonParser>
{
    int IdChat;
    std::vector<std::string> mes_vec;

    void parseJSON();
    void dbWork();
    void createResponse();

public:
    LoadChatPartService() = delete;
    LoadChatPartService(std::shared_ptr<Queue<ResponseStruct>> q);
    LoadChatPartService(DB& database, Parser& parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    ~LoadChatPartService();

};

template<class DB, class Parser>
class NewMessageService : public virtual AbstractService<DBWorker, JsonParser>
{
    int IdChat;
    ChatMessage message;

    void parseJSON();
    void dbWork();
    void createResponse();

public:
    NewMessageService() = delete;
    NewMessageService(std::shared_ptr<Queue<ResponseStruct>> q);
    NewMessageService(DB& database, Parser& parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    ~NewMessageService();
};

template<class DB, class Parser>
class NewChatService : public virtual AbstractService<DBWorker, JsonParser>
{
    std::string ChatName;
    std::vector<int> user_id_vec;

    void parseJSON();
    void dbWork();
    void createResponse();

public:
    NewChatService();
    NewChatService(std::shared_ptr<Queue<ResponseStruct>> q);
    NewChatService(DB& database, Parser& parser, std::shared_ptr<Queue<ResponseStruct>> queue);
    ~NewChatService();
};


template<class DB, class Parser>
AbstractService<DB, Parser>::AbstractService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> queue) {
    queueOut = queue;
}

template<class DB, class Parser>
void AbstractService<DB, Parser>::DoLogic() {
    while(true) {
        std::mutex lock;
        std::unique_lock<std::mutex> ul(lock);
        bell.wait(ul, [&]() { return !queueIn.UnsafeIsEmpty(); });
        lock.unlock();

        if (queueIn.Front() == "KILL"){
            break;
        }
        else{
            LogicRealize();
        }
    }
}

template<class DB, class Parser>
void AbstractService<DB, Parser>::Kill() {
    PushRequest("KILL");
    thread.join();
}

template<class DB, class Parser>
void AbstractService<DB, Parser>::PushRequest(std::string json) {
    queueIn.Add(json);
    bell.notify_one();
}

template<class DB, class Parser>
void AbstractService<DB, Parser>::Run() {
    thread = std::thread(&AbstractService<DB, Parser>::DoLogic, std::ref(*this));
}

template<class DB, class Parser>
AbstractService<DB, Parser>::AbstractService(std::shared_ptr<Queue<ResponseStruct>> q) {
    queueOut = q;
}

template<class DB, class Parser>
void NewUserService<DB, Parser>::parseJSON() {

}

template<class DB, class Parser>
void NewUserService<DB, Parser>::dbWork() {

}

template<class DB, class Parser>
void NewUserService<DB, Parser>::createResponse() {

}

template<class DB, class Parser>
NewUserService<DB, Parser>::NewUserService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> q)
{
    dbw = database;
}

template<class DB, class Parser>
NewUserService<DB, Parser>::NewUserService(std::shared_ptr<Queue<ResponseStruct>> q){
    queueOut = q;
}

template<class DB, class Parser>
NewUserService<DB, Parser>::~NewUserService() = default;


template<class DB, class Parser>
void LoginService<DB, Parser>::parseJSON() {

}

template<class DB, class Parser>
void LoginService<DB, Parser>::dbWork() {
    //dbw.setIter("login", login);
    ///// проверить если такого нет
    //std::string tmpPassword;
    //tmpPassword = dbw.GetStr("password");
    //if (password == tmpPassword){
    //    isDataRight = true;
    //}
}

template<class DB, class Parser>
void LoginService<DB, Parser>::createResponse() {

}

template<class DB, class Parser>
LoginService<DB, Parser>::LoginService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> q){
    dbw = database;
    isDataRight = false;
}

template<class DB, class Parser>
LoginService<DB, Parser>::LoginService(std::shared_ptr<Queue<ResponseStruct>> q) {
    queueOut = q;
}

template<class DB, class Parser>
LoginService<DB, Parser>::~LoginService() = default;


template<class DB, class Parser>
void LoadChatPartService<DB, Parser>::parseJSON() {

}

template<class DB, class Parser>
void LoadChatPartService<DB, Parser>::dbWork() {
    //int mes_part = 25;
    //int num = 0;
    //dbw.setIter("chat_id", IdChat);
    //num = dbw.GetInt("message_num");
//
    //if (num < mes_part){
    //    mes_part = num;
    //}
//
    //dbw.setIterMany("chat_id", IdChat, 0, mes_part);


}

template<class DB, class Parser>
void LoadChatPartService<DB, Parser>::createResponse() {

}

template<class DB, class Parser>
LoadChatPartService<DB, Parser>::LoadChatPartService(std::shared_ptr<Queue<ResponseStruct>> q){
    std::string str = "Chat_";
    str += IdChat;
    dbw = DBWorker(str);
    queueOut = q;
}

template<class DB, class Parser>
LoadChatPartService<DB, Parser>::LoadChatPartService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> q)
{
    dbw = database;
}

template<class DB, class Parser>
LoadChatPartService<DB, Parser>::~LoadChatPartService() = default;

template<class DB, class Parser>
void NewMessageService<DB, Parser>::parseJSON() {

}

template<class DB, class Parser>
void NewMessageService<DB, Parser>::dbWork() {
    //int num = 0;
    //dbw.setIter("chat_id", IdChat);
    //num = dbw.GetInt("message_num");
    //++num;
    //std::string str = "chat";
    //str += IdChat;
    //dbw.updateInt(str, "chat_id", IdChat, "message_num", num);
//
    //std::stringstream ss;
    //ss << num;
    //std::map<std::string, std::string> m;
    //m["user_id"] = message.IdUser;
    //m["message"] = message.message;
    //m["time"] = message.time;
    //dbw.AddMap(ss.str(), m);
    //dbw.saveDoc();
}

template<class DB, class Parser>
void NewMessageService<DB, Parser>::createResponse() {

}

template<class DB, class Parser>
NewMessageService<DB, Parser>::NewMessageService(std::shared_ptr<Queue<ResponseStruct>> q){
    queueOut =q;
}

template<class DB, class Parser>
NewMessageService<DB, Parser>::NewMessageService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> q)
{
    dbw = database;
}

template<class DB, class Parser>
NewMessageService<DB, Parser>::~NewMessageService() = default;



template<class DB, class Parser>
void NewChatService<DB, Parser>::parseJSON() {

}

template<class DB, class Parser>
void NewChatService<DB, Parser>::dbWork() {

}

template<class DB, class Parser>
void NewChatService<DB, Parser>::createResponse() {

}

template<class DB, class Parser>
NewChatService<DB, Parser>::NewChatService() = default;

template<class DB, class Parser>
NewChatService<DB, Parser>::NewChatService(DB &database, Parser &parser, std::shared_ptr<Queue<ResponseStruct>> q)
{

}

template<class DB, class Parser>
NewChatService<DB, Parser>::NewChatService(std::shared_ptr<Queue<ResponseStruct>> q){
    queueOut = q;
}

template<class DB, class Parser>
NewChatService<DB, Parser>::~NewChatService() = default;
