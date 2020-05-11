#pragma once

#include <map>
#include <queue>
#include "../JsonParser/JsonParser.h"
#include "../Services/Services.h"

template <class Parser>
class BusinessLogic
{
    Parser jsp;
    std::map<std::string, AbstractService<DBWorker, JsonParser>*> workers;
    std::queue<ResponseStruct>* QueueOut;

    int getCMD(const std::string& filepath, std::string& CMD);
public:

    BusinessLogic();
    BusinessLogic(Parser& ps);
    int SetRequest(const std::string& JsonStr);
    ResponseStruct GetResponse();
    ~BusinessLogic();
};
