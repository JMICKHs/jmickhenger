//
// Created by nick on 15.04.2020.
//

#ifndef JMICKHENGER_CONNECTION_H
#define JMICKHENGER_CONNECTION_H

struct ResponseStruct {

}typedef ResponseStruct;


class Connection {
private:
    ip::tcp::socket socket;
    int connection_id;
    std::string read_buffer;
    ResponseStruct write_buffer;
public:
    void new_session();
    void start_session();
    void stop_session();
    bool is_active();
};


#endif //JMICKHENGER_CONNECTION_H
