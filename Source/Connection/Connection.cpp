//
// Created by nick on 02.05.2020.
//

#include "Connection.h"

using namespace boost::asio;
io_service service;
int a = 0;


#define MEM_FN1(x,y)    boost::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z)  boost::bind(&self_type::x, shared_from_this(),y,z)

void Connection::start() {
    started_ = true;
    socket.async_read_some(buffer(read_buffer_), MEM_FN2(on_read,_1,_2));
    std::cout << read_buffer_;
}

Connection::ptr Connection::new_(int index) {
    return ptr(new Connection(std::shared_ptr<Connection>(), index));
}

ip::tcp::socket &Connection::get_socket() {
    return socket;
}

void Connection::on_read(const Connection::error_code &err, size_t bytes) {
    if ( !err) {
        std::cout << read_buffer_ << std::endl;
        std::string response(read_buffer_, bytes);
        response += "\n";
        do_write(response + "\n");
    }

}

void Connection::on_write(const Connection::error_code &err, size_t bytes) {
    socket.async_read_some(buffer(read_buffer_), MEM_FN2(on_read,_1,_2));
}

void Connection::do_write(const std::string &msg) {
    std::copy(msg.begin(), msg.end(), write_buffer_);
    socket.async_write_some( buffer(write_buffer_, msg.size()),
                            MEM_FN2(on_write,_1,_2));
}

Connection::Connection(std::shared_ptr<Connection> sharedPtr, int index)
        : socket(service), started_(false), connection_id(index) {
    std::cout << "new Connection #" << index << std::endl;
}

void Connection::new_session() {

}

void Connection::start_session() {

}

void Connection::stop_session() {

}

bool Connection::is_active() {
    return started_;
}

void Connection::handle_write() {

}

void Connection::handle_read() {

}
