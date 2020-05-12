//
// Created by nick on 15.04.2020.
//


#include "BusinessLogicProxy.h"
#include <boost/bind.hpp>
#include <cstring>
#include <algorithm>

int BusinessLogicProxy::watch_first_package_id() {
// необходим экземпляр бизнес-логики
}


void BusinessLogicProxy::enter(std::shared_ptr<abstract_Connection> abstract_Connection, const std::string &nickname) {
    connections_.insert(abstract_Connection);
    client_collection[abstract_Connection] = nickname;
    std::for_each(recent_msgs_.begin(), recent_msgs_.end(),
                  boost::bind(&abstract_Connection::on_message, abstract_Connection, _1));
}

void BusinessLogicProxy::leave(std::shared_ptr<abstract_Connection> abstract_Connection) {
    connections_.erase(abstract_Connection);
    client_collection.erase(abstract_Connection);
}

void BusinessLogicProxy::mailing(std::array<char, MAX_IP_PACK_SIZE> &msg,
                                   std::shared_ptr<abstract_Connection> abstract_Connection) {

    std::string nickname = get_name(abstract_Connection);
    std::array<char, MAX_IP_PACK_SIZE> formatted_msg = {};

    strcat(formatted_msg.data(), msg.data());
    strcat(formatted_msg.data(), "\r\n");

    recent_msgs_.push_back(formatted_msg);

    while (recent_msgs_.size() > max_recent_msgs)
    {
        recent_msgs_.pop_front();
    }

    std::for_each(connections_.begin(), connections_.end(),
                  boost::bind(&abstract_Connection::on_message, _1, std::ref(formatted_msg)));
}

std::string BusinessLogicProxy::get_name(std::shared_ptr<abstract_Connection> abstract_Connection) {
    return client_collection[abstract_Connection];
}