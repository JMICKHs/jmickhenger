#pragma once

#include <queue>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include "../SupportStructures/SupportSructures.h"
#include "../JsonParser/JsonParser.h"
#include "../DBWorker/DBWorker.h"


template<class DB, class Parser>
class AbstractService
{
protected:
    std::string JsonStr;
    Parser jsp;
    DB dbw;
    std::queue<ResponseStruct>* queueOut;
    std::queue<std::string> queueIn;
    std::thread thread;
    std::recursive_mutex lock;

    virtual void parseJSON() = 0;
    virtual void dbWork() = 0;
    virtual void createResponse() = 0;

public:
    AbstractService();
    AbstractService(DB& database, Parser& parser, std::queue<ResponseStruct>* queue);;
    void LogicRealize(){};
    static void DoLogic(AbstractService* obj);
    ~AbstractService()= default;
};

template<class DB, class Parser>
class NewUserService : public virtual AbstractService<DB, Parser>
{
    std::string login;
    std::string password;
    std::string avatar_path;

    void parseJSON();
    void dbWork();
    void createResponse();

public:
    NewUserService();
    NewUserService(DB& database, Parser& parser, std::queue<ResponseStruct>* queue);
    ~NewUserService();
};

template<class DB, class Parser>
class LoginService : public virtual AbstractService<DB, Parser>
{
    std::string login;
    std::string password;

    void parseJSON();
    void dbWork();
    void createResponse();

public:
    LoginService();
    LoginService(DB& database, Parser& parser, std::queue<ResponseStruct>* queue);
    ~LoginService();
};

template<class DB, class Parser>
class LoadChatPartService : public virtual AbstractService<DB, Parser>
{
    int IdChat;
    std::vector<std::string> mes_vec;

    void parseJSON();
    void dbWork();
    void createResponse();

public:
    LoadChatPartService();
    LoadChatPartService(DB& database, Parser& parser, std::queue<ResponseStruct>* queue);
    ~LoadChatPartService();

};

template<class DB, class Parser>
class NewMessageService : public virtual AbstractService<DB, Parser>
{
    int IdChat;
    ChatMessage message;

    void parseJSON();
    void dbWork();
    void createResponse();

public:
    NewMessageService();
    NewMessageService(DB& database, Parser& parser, std::queue<ResponseStruct>* queue);
    ~NewMessageService();
};

template<class DB, class Parser>
class NewChatService : public  virtual AbstractService<DB, Parser>
{
    std::string ChatName;
    std::vector<int> user_id_vec;

    void parseJSON();
    void dbWork();
    void createResponse();

public:
    NewChatService();
    NewChatService(DB& database, Parser& parser, std::queue<ResponseStruct>* queue);
    ~NewChatService();
};
