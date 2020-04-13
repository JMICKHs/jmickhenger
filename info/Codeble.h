//
// Created by Sergei Alexeev on 11.04.2020.
//

#ifndef APP_NETWORK_CODEBLE_H
#define APP_NETWORK_CODEBLE_H


#include <string>
#include "../app-network/parser-json/Parser.h"
using namespace std;

class Codeble {
public:
    virtual string encode() = 0;
    virtual void decode(string pathToJson) = 0;
protected:
    Parser parser;
};


#endif //APP_NETWORK_CODEBLE_H
