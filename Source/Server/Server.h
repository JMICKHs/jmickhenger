//
// Created by nick on 15.04.2020.
//

#ifndef JMICKHENGER_SERVER_H
#define JMICKHENGER_SERVER_H


class Server {
private:
    boost::asio::io_service service;
    ip::tcp::acceptor acceptor;
    endpoint endpoint;
    std::vector<std::thread> threads;
    std::map(Connection client, int connection_id);

public:
    Server();
    void run_server();
    void stop_server();
};


#endif //JMICKHENGER_SERVER_H
