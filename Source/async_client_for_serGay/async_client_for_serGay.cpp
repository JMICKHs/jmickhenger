//
// Created by nick on 28.04.2020.
//

#ifdef WIN32
#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#include <iostream>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
using namespace boost::asio;
io_service service;

#define MEM_FN(x)       boost::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x,y)    boost::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z)  boost::bind(&self_type::x, shared_from_this(),y,z)

class client : public boost::enable_shared_from_this<client>
        , boost::noncopyable {
    typedef client self_type;
    client(const std::string & message)
            : sock_(service), started_(true), message_(message) {}
    void start(ip::tcp::endpoint ep) {
        sock_.async_connect(ep, MEM_FN1(on_connect,_1));
    }
public:
    typedef boost::system::error_code error_code;
    typedef boost::shared_ptr<client> ptr;

    static ptr start(ip::tcp::endpoint ep, const std::string & message) {
        std::cout << "start new connection " << std::endl;
        ptr new_(new client(message));
        new_->start(ep);
        return new_;
    }
    void stop() {
        if ( !started_) return;
        started_ = false;
        sock_.close();
    }
    bool started() { return started_; }
private:
    void on_connect(const error_code & err) {
        do_write(message_ + "\n");
        sock_.async_read_some(buffer(read_buffer_), MEM_FN2(on_read,_1,_2));
    }
    void on_read(const error_code & err, size_t bytes) {
        if ( !err) {
            std::cout << "server: > " << read_buffer_ << std::endl;
            std::cout << "ur msg: > ";
            std::cin.getline(write_buffer_,128);
            sock_.async_write_some(buffer(write_buffer_), MEM_FN2(on_write, _1, _2));
        }
    }

    void on_write(const error_code & err, size_t bytes) {
        sock_.async_read_some(buffer(read_buffer_), MEM_FN2(on_read,_1,_2));
    }
    void do_read() {
        async_read(sock_, buffer(read_buffer_),
                   MEM_FN2(read_complete,_1,_2), MEM_FN2(on_read,_1,_2));
    }
    void do_write(const std::string & msg) {
        if ( !started() ) return;
        std::copy(msg.begin(), msg.end(), write_buffer_);
        sock_.async_write_some( buffer(write_buffer_, msg.size()),
                                MEM_FN2(on_write,_1,_2));
    }
    size_t read_complete(const boost::system::error_code & err, size_t bytes) {
        if ( err) return 0;
        bool found = std::find(read_buffer_, read_buffer_ + bytes, '\n') < read_buffer_ + bytes;
        return found ? 0 : 1;
    }

private:
    ip::tcp::socket sock_;
    enum { max_msg = 1024 };
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    bool started_;
    std::string message_;
};

int main(int argc, char* argv[]) {
//    TODO: тут пока локалхост, когда будем подключены к одной сети, то изменим адрес
    ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 8001);
    client::start(ep, "hello");
//    TODO: в стартовом сообщении можно отправлять какой-нибудь идентификатор для сервера
//
    service.run();
}