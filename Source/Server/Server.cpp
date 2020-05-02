//
// Created by nick on 15.04.2020.
//

#include "Server.h"
#include "../Connection/Connection.h"

ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 8000);

Server::Server(boost::asio::io_service &io_service)
        : io_service_(io_service), acceptor_(io_service,ep), user_count(0) {
}

Server::ptr Server::create() {
    return std::make_shared<Server>(service);
}

void Server::handle_accept(const Connection::ptr &new_Connection, const boost::system::error_code &error) {
    if (!error) {
        new_Connection->start();
        Connection::ptr new_connection2 = Connection::new_(user_count);
        client_collection[user_count++] = std::shared_ptr<Connection>(new_connection2);

        acceptor_.async_accept(new_connection2->get_socket(),
                               boost::bind(&Server::handle_accept, shared_from_this(), new_connection2,
                                           boost::asio::placeholders::error));
    }

}

void Server::run_server() {
    Connection::ptr new_connection = Connection::new_(user_count);
    client_collection[user_count++] = std::shared_ptr<Connection>(new_connection);
    acceptor_.async_accept(new_connection->get_socket(),
                           boost::bind(&Server::handle_accept, shared_from_this(), new_connection,
                                       boost::asio::placeholders::error));

}

void Server::stop_server() {

}

void Server::start_accept() {

}
