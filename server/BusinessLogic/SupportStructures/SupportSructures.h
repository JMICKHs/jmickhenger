#pragma once

#include <vector>
#include <string>


struct ChatMessage {
    std::string message;
    std::string image;
    int IdUser;
    int time;
    bool checked;
    int number;

    ChatMessage(const std::string &mes = "", const std::string &img = "", int id = -1, int _time = 0,
                bool _checked = false, int num = -1) : message(mes), image(img), IdUser(id), time(_time),
                                                       checked(_checked), number(num) {};
};


struct ResponseStruct
{
    std::string Json;
    int ServerId;
    int RealId;

    ResponseStruct() = default;
    ResponseStruct(const std::string& _json, int realId, int servId = 1) : Json(_json), RealId(realId), ServerId(servId) {};
    ~ResponseStruct() = default;
};
