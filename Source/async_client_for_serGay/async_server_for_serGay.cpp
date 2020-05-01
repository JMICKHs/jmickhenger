#ifdef WIN32
#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif


#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
using namespace boost::asio;
using namespace boost::posix_time;
io_service service;

#define MEM_FN1(x,y)    boost::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z)  boost::bind(&self_type::x, shared_from_this(),y,z)

int a = 0;
class connection : public boost::enable_shared_from_this<connection>, boost::noncopyable {
    typedef connection self_type;
    connection() : sock_(service), started_(false), index_connection(a) {
        a++;
        std::cout << "new connection #" << a <<std::endl;}
public:
    typedef boost::system::error_code error_code;
    typedef boost::shared_ptr<connection> ptr;

    void start() {
        started_ = true;
        sock_.async_read_some(buffer(read_buffer_), MEM_FN2(on_read,_1,_2));
        std::cout << read_buffer_;
    }
    static ptr new_() {
        ptr new_(new connection);
        return new_;
    }

    ip::tcp::socket & sock() { return sock_;}
private:
    void on_read(const error_code & err, size_t bytes) {
        if ( !err) {
            std::cout << read_buffer_ << std::endl;
            std::string response(read_buffer_, bytes);
            response += "\n";
            do_write(response + "\n");
        }
    }

    void on_write(const error_code & err, size_t bytes) {
        sock_.async_read_some(buffer(read_buffer_), MEM_FN2(on_read,_1,_2));
    }
    void do_write(const std::string & msg) {
        std::copy(msg.begin(), msg.end(), write_buffer_);
        sock_.async_write_some( buffer(write_buffer_, msg.size()),
                                MEM_FN2(on_write,_1,_2));
    }
private:
    ip::tcp::socket sock_;
    enum { max_msg = 1024 };
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    bool started_;
    int index_connection;
};
ip::tcp::endpoint ep( ip::address::from_string("192.168.1.101"), 8001);

ip::tcp::acceptor acceptor(service, ep );

void handle_accept(connection::ptr client, const boost::system::error_code & err) {
    client->start();
    connection::ptr new_client = connection::new_();
    acceptor.async_accept(new_client->sock(), boost::bind(handle_accept,new_client,_1));
}


int main(int argc, char* argv[]) {
    connection::ptr client = connection::new_();
    acceptor.async_accept(client->sock(), boost::bind(handle_accept,client,_1));
    service.run();
}

