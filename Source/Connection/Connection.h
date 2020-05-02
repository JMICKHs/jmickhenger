//
// Created by nick on 15.04.2020.
//

#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H


#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class Connection : public std::enable_shared_from_this<Connection> {
    typedef Connection self_type;
    Connection(std::shared_ptr<Connection> sharedPtr, int index);
public:
    typedef boost::system::error_code error_code;
    typedef std::shared_ptr<Connection> ptr;

    void start();
    static ptr new_(int index);

    void new_session();

    void start_session();
    void stop_session();
    bool is_active();

    boost::asio::ip::tcp::socket &get_socket();
private:
    void on_read(const error_code & err, size_t bytes);

    void on_write(const error_code & err, size_t bytes);
    void do_write(const std::string & msg);

    void handle_write();
    void handle_read();
private:
    boost::asio::ip::tcp::socket socket;
    enum { max_msg = 1024 };
//    std::string read_buffer;
//    ResponseStruct write_buffer;
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    bool started_;
    int connection_id;
};

#endif //TCP_CONNECTION_H



