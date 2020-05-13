//
// Created by nick on 15.04.2020.
//

#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H


#include "AbstractConnection.h"
#include <array>
#include "../BusinessLogicProxy/BusinessLogicProxy.h"

using boost::asio::ip::tcp;

class Connection : public abstract_Connection,
        public std::enable_shared_from_this<Connection> {
    typedef Connection self_type;
public:
    Connection(boost::asio::io_service& io_service,
               boost::asio::io_service::strand& strand, BusinessLogicProxy& room)
            : socket_(io_service), strand_(strand), room_(room)
    {
    }
public:
    typedef boost::system::error_code error_code;
    typedef std::shared_ptr<Connection> ptr;


    tcp::socket& socket();
    bool readCondition(const boost::system::error_code &err, size_t length);

    void start();

    void on_message(std::array<char, MAX_IP_PACK_SIZE>& msg);

private:


    void name_handler(const boost::system::error_code& error);

    void read_handler(const boost::system::error_code& error);

    void write_handler(const boost::system::error_code& error);

private:
    tcp::socket socket_;
    boost::asio::io_service::strand& strand_;
    BusinessLogicProxy& room_;
    std::array<char, MAX_NICKNAME> nickname_;
    std::array<char, MAX_IP_PACK_SIZE> read_msg_;
    int connection_id;
    std::deque<std::array<char, MAX_IP_PACK_SIZE> > write_msgs_;
};

#endif //TCP_CONNECTION_H



