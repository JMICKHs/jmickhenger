#pragma once

#include <vector>
#include <string>


struct ChatMessage
{
    std::string message;
    int IdUser;
    std::string time;
};


struct ResponseStruct
{
    std::string filepath;
    std::string CMD;
    std::vector<int> IdUsers;
};