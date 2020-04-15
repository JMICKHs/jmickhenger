//
// Created by Sergei Alexeev on 13.04.2020.
//

#ifndef NETWORK_CACHE_CODEBLE_H
#define NETWORK_CACHE_CODEBLE_H


#include <string>
#include "../parser/Parser.h"
using namespace std;

class Codeble {
public:
    virtual string encode() = 0;
    virtual void decode(string json) = 0;
protected:
    Parser parser;
    //Parser parser;
};


#endif //NETWORK_CACHE_CODEBLE_H
