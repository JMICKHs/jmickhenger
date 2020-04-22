//
// Created by nick on 15.04.2020.
//

#ifndef JMICKHENGER_BUSINESSLOGICPROXY_H
#define JMICKHENGER_BUSINESSLOGICPROXY_H
//include "Business-Logic"

struct ResponseStruct {

}typedef ResponseStruct;


class BusinessLogicProxy {
private:
    ResponseStruct read_buffer;
    std::string write_buffer;

public:
    int enqueue(std::string msg);
    ResponseStruct dequeue();
    int watch_first_package_id();
};


#endif //JMICKHENGER_BUSINESSLOGICPROXY_H
