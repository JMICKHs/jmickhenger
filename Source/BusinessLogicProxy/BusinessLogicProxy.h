//
// Created by nick on 15.04.2020.
//

#ifndef JMICKHENGER_BUSINESSLOGICPROXY_H
#define JMICKHENGER_BUSINESSLOGICPROXY_H
//include "Business-Logic"

#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "../async_client_for_serGay/config.h"
#include "../Connection/AbstractConnection.h"
class BusinessLogicProxy {
public:
    void enter(std::shared_ptr<abstract_Connection> abstract_Connection, const std::string & nickname);

    void leave(std::shared_ptr<abstract_Connection> abstract_Connection);

    void mailing(std::array<char, MAX_IP_PACK_SIZE>& msg, std::shared_ptr<abstract_Connection> abstract_Connection);

    std::string get_name(std::shared_ptr<abstract_Connection> abstract_Connection);

    int watch_first_package_id();

private:
    enum { max_recent_msgs = 100 };
    std::unordered_set<std::shared_ptr<abstract_Connection>> connections_;
    std::unordered_map<std::shared_ptr<abstract_Connection>, std::string> client_collection;
    std::deque<std::array<char, MAX_IP_PACK_SIZE>> recent_msgs_;
};

#endif  // JMICKHENGER_BUSINESSLOGICPROXY_H
