//
// Created by nick on 15.04.2020.
//

#include "Server.h"
#include "../Connection/Connection.h"
#include <boost/asio.hpp>
#include "../BusinessLogicProxy/BusinessLogicProxy.h"
#include <boost/thread/thread.hpp>
#include <thread>
#include <mutex>

Server::Server(boost::asio::io_service& io_service,
boost::asio::io_service::strand& strand, const tcp::endpoint& endpoint) : io_service_(io_service),
                                        strand_(strand),
                                        acceptor_(io_service, endpoint) {
    run();
}


void Server::run() {
    std::shared_ptr<Connection> new_abstract_Connection(new Connection(io_service_, strand_, room_));
    acceptor_.async_accept(new_abstract_Connection->socket(), strand_.wrap(boost::bind(&Server::on_accept, this, new_abstract_Connection, _1)));
}

void Server::on_accept(std::shared_ptr<Connection> new_abstract_Connection, const boost::system::error_code& error) {
    if (!error) {
        new_abstract_Connection->start();
    }
    run();
}
