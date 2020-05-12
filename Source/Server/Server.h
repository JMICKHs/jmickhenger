//
// Created by nick on 15.04.2020.
//

#ifndef JMICKHENGER_SERVER_H
#define JMICKHENGER_SERVER_H


#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "../Connection/Connection.h"

using namespace boost::asio;

using boost::asio::ip::tcp;

class Server: public std::enable_shared_from_this<Server>  {
public:
    explicit Server(boost::asio::io_service& io_service);
    Server(boost::asio::io_service& io_service,
           boost::asio::io_service::strand& strand,
           const tcp::endpoint& endpoint);
    ~Server() = default;
    typedef std::shared_ptr<Server> ptr;

private:

    void run();

    void on_accept(std::shared_ptr<Connection> new_abstract_Connection, const boost::system::error_code& error);

//    BusinessLogicProxy BusinessLogicProxy_;
    boost::asio::io_service &io_service_;
    tcp::acceptor acceptor_;
    boost::asio::io_service::strand& strand_;
    BusinessLogicProxy room_;
//    endpoint endpoint;
//    std::vector<std::thread> threads;
    std::map<int, std::shared_ptr<Connection>> client_collection;
//    std::deque<>
    int user_count;
};

#endif //JMICKHENGER_SERVER_H
