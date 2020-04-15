#include "Services.h"


template<class DB, class Parser>
AbstractService<DB, Parser>::AbstractService() = default;

template<class DB, class Parser>
AbstractService<DB, Parser>::AbstractService(DB &database, Parser &parser, std::queue<ResponseStruct> *queue) {
    queueOut = queue;
}

template<class DB, class Parser>
void AbstractService<DB, Parser>::DoLogic(AbstractService *obj) {

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
NewUserService<DB, Parser>::NewUserService() = default;

template<class DB, class Parser>
NewUserService<DB, Parser>::NewUserService(DB &database, Parser &parser, std::queue<ResponseStruct> *queue)
{

}

template<class DB, class Parser>
NewUserService<DB, Parser>::~NewUserService() = default;


template<class DB, class Parser>
void LoginService<DB, Parser>::parseJSON() {

}

template<class DB, class Parser>
void LoginService<DB, Parser>::dbWork() {

}

template<class DB, class Parser>
void LoginService<DB, Parser>::createResponse() {

}

template<class DB, class Parser>
LoginService<DB, Parser>::LoginService() = default;

template<class DB, class Parser>
LoginService<DB, Parser>::LoginService(DB &database, Parser &parser, std::queue<ResponseStruct> *queue){

}

template<class DB, class Parser>
LoginService<DB, Parser>::~LoginService() = default;



template<class DB, class Parser>
void LoadChatPartService<DB, Parser>::parseJSON() {

}

template<class DB, class Parser>
void LoadChatPartService<DB, Parser>::dbWork() {

}

template<class DB, class Parser>
void LoadChatPartService<DB, Parser>::createResponse() {

}

template<class DB, class Parser>
LoadChatPartService<DB, Parser>::LoadChatPartService() = default;

template<class DB, class Parser>
LoadChatPartService<DB, Parser>::LoadChatPartService(DB &database, Parser &parser, std::queue<ResponseStruct> *queue)
{

}

template<class DB, class Parser>
LoadChatPartService<DB, Parser>::~LoadChatPartService() = default;

template<class DB, class Parser>
void NewMessageService<DB, Parser>::parseJSON() {

}

template<class DB, class Parser>
void NewMessageService<DB, Parser>::dbWork() {

}

template<class DB, class Parser>
void NewMessageService<DB, Parser>::createResponse() {

}

template<class DB, class Parser>
NewMessageService<DB, Parser>::NewMessageService() = default;

template<class DB, class Parser>
NewMessageService<DB, Parser>::NewMessageService(DB &database, Parser &parser, std::queue<ResponseStruct> *queue)
{

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
NewChatService<DB, Parser>::NewChatService(DB &database, Parser &parser, std::queue<ResponseStruct> *queue)
{

}

template<class DB, class Parser>
NewChatService<DB, Parser>::~NewChatService() = default;
