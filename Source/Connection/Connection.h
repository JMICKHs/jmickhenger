//
// Created by nick on 15.04.2020.
//

#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H


#include "AbstractConnection.h"
#include <array>
#include "../BusinessLogicProxy/BusinessLogicProxy.h"
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/ssl/stream.hpp>

using boost::asio::ip::tcp;
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

class Connection : public abstract_Connection,
        public std::enable_shared_from_this<Connection> {
    typedef Connection self_type;
public:
    Connection(boost::asio::io_service& io_service,
               boost::asio::ssl::context& context,
               boost::asio::io_service::strand& strand,
               BusinessLogicProxy& room)
            : socket_(io_service, context), strand_(strand), room_(room)
    {
    }
public:


    ssl_socket::lowest_layer_type& socket();

    typedef boost::system::error_code error_code;
    typedef std::shared_ptr<Connection> ptr;


    void handshake();

    void start(const boost::system::error_code& error);

    void on_message(std::array<char, MAX_IP_PACK_SIZE>& msg);

private:


    void name_handler(const boost::system::error_code& error);

    void read_handler(const boost::system::error_code& error);

    void write_handler(const boost::system::error_code& error);

private:
    ssl_socket socket_;
    boost::asio::io_service::strand& strand_;
    BusinessLogicProxy& room_;
    std::array<char, MAX_NICKNAME> nickname_;
    boost::asio::streambuf read_msg_;
    std::deque<std::string> write_msgs_;
};

#endif //TCP_CONNECTION_H



