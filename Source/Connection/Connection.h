//
// Created by nick on 15.04.2020.
//

#ifndef JMICKHENGER_CONNECTION_H
#define JMICKHENGER_CONNECTION_H

struct ResponseStruct {

}typedef ResponseStruct;


class Connection {

public:
    void new_session();
    void start_session();
    void stop_session();
    bool is_active();
    tcp::socket &get_socket();

private:
    void handle_write();
    void handle_read();


    ip::tcp::socket socket;
    int connection_id;
    std::string read_buffer;
    ResponseStruct write_buffer;
};


#endif //JMICKHENGER_CONNECTION_H
