//
// Created by nick on 15.04.2020.
//

#include "Server.h"
#include "../Connection/Connection.h"
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <thread>
#include <mutex>

Server::Server(boost::asio::io_service& io_service,
boost::asio::io_service::strand& strand, const tcp::endpoint& endpoint) : io_service_(io_service),
                                        strand_(strand),
                                        acceptor_(io_service, endpoint),
                                        context_(boost::asio::ssl::context::sslv23) {
    context_.set_options(
            boost::asio::ssl::context::default_workarounds
            | boost::asio::ssl::context::no_sslv2
            | boost::asio::ssl::context::single_dh_use);
    context_.set_password_callback(boost::bind(&Server::get_password, this));
    context_.use_certificate_chain_file("Server.pem");
    context_.use_private_key_file("Server.pem", boost::asio::ssl::context::pem);
    context_.use_tmp_dh_file("dh512.pem");
    run();
}

std::string Server::get_password() const {
    return "test";
}

void Server::run() {
    std::shared_ptr<Connection> new_abstract_Connection(new Connection(io_service_,context_, strand_, room_));
    acceptor_.async_accept(new_abstract_Connection->socket(), strand_.wrap(boost::bind(&Server::on_accept, this, new_abstract_Connection, _1)));
}

void Server::on_accept(std::shared_ptr<Connection> new_abstract_Connection, const boost::system::error_code& error) {
    if (!error) {
        new_abstract_Connection->handshake();
    }
    run();
}
