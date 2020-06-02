//
// Created by nick on 11.05.2020.
//

#ifndef TCP_ABSTRACTCONNECTION_H
#define TCP_ABSTRACTCONNECTION_H

#include "../async_client_for_serGay/config.h"
#include <iostream>
#include <boost/asio/detail/array.hpp>
class abstract_Connection {
public:
    virtual ~abstract_Connection() {}
    virtual void on_message(std::array<char, MAX_IP_PACK_SIZE> & msg) = 0;
};


#endif //TCP_ABSTRACTCONNECTION_H
