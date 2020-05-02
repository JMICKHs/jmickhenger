//
// Created by nick on 15.04.2020.
//

#ifndef JMICKHENGER_SERVER_H
#define JMICKHENGER_SERVER_H


#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "../Connection/Connection.h"

using namespace boost::asio;
//extern ip::tcp::endpoint ep;

extern io_service service;


using boost::asio::ip::tcp;

class Server: public std::enable_shared_from_this<Server>  {
public:
    explicit Server(boost::asio::io_service& io_service);
    ~Server() = default;
    typedef std::shared_ptr<Server> ptr;
    static ptr create();
    void run_server();
    void stop_server();
private:
    void handle_accept(const Connection::ptr& new_Connection,
                       const boost::system::error_code & error);
    void start_accept();
private:
    boost::asio::io_service &io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
//    endpoint endpoint;
//    std::vector<std::thread> threads;
    std::map<int, std::shared_ptr<Connection>> client_collection;

    int user_count;
//    BusinessLogicProxy BusinessLogicProxy_;
};

#endif //JMICKHENGER_SERVER_H
