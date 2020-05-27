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
#include <boost/asio/streambuf.hpp>
#include "../async_client_for_serGay/config.h"
#include "../Connection/AbstractConnection.h"
#include "../BusinessLogic/Business-Logic/Business-Logic.hpp"

class BusinessLogicProxy {
public:
    void enter(std::shared_ptr<abstract_Connection> abstract_Connection, const std::string & nickname);

    void leave(std::shared_ptr<abstract_Connection> abstract_Connection);

    void mailing(boost::asio::streambuf& msg, std::shared_ptr<abstract_Connection> abstract_Connection);

private:
    enum { max_recent_msgs = 100 };
    std::unordered_set<std::shared_ptr<abstract_Connection>> connections_;
    int negative_id = -1;
    std::vector<int> alive_users_id;
    std::unordered_map<int, std::shared_ptr<abstract_Connection>> id_collection;
    std::deque<std::array<char, MAX_IP_PACK_SIZE>> recent_msgs_;
    BusinessLogic<JsonParser> msg_queue;

};

#endif  // JMICKHENGER_BUSINESSLOGICPROXY_H
