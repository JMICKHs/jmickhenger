//
// Created by nick on 15.04.2020.
//

#ifndef JMICKHENGER_SERVER_H
#define JMICKHENGER_SERVER_H


class Server {

public:
    Server();
    ~Server;
    void run_server();
    void stop_server();
private:
    boost::asio::io_service service;
    ip::tcp::acceptor acceptor;
    endpoint endpoint;
    std::vector<std::thread> threads;
    std::map(Connection client, int connection_id);
    BusinessLogicProxy BusinessLogicProxy_;

    void handle_accept();
    void start_accept();
};


#endif //JMICKHENGER_SERVER_H
