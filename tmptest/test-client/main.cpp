//
// Created by nick on 01.05.2020.
//

#ifdef WIN32
#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif


#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "info/Info.h"
using namespace boost::asio;
using namespace boost::posix_time;
io_service service;
//ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));
ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 8000);

#define MEM_FN1(x,y)    boost::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z)  boost::bind(&self_type::x, shared_from_this(),y,z)

int a = 0;
class connection : public boost::enable_shared_from_this<connection> {
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
        return ptr(new connection);
    }

    ip::tcp::socket & sock() { return sock_;}
private:
    void on_read(const error_code & err, size_t bytes) {
        if ( !err) {
            std::cout << read_buffer_ << std::endl;
            std::string response(read_buffer_, bytes);
            response += "\n";
            do_write(response + "\r\n");
        }
    }

    void on_write(const error_code & err, size_t bytes) {
        sock_.async_read_some(buffer(read_buffer_), MEM_FN2(on_read,_1,_2));
    }
    void do_write(const std::string & msg) {
        using namespace inf;
        Query q;
        q.decode(msg);
        string tmp;
        switch (q.cmd) {
            case (2): {
                Parser parser;
                parser.setJson(q.body);
                string nick = parser.getStr(MyAccount::nameLogin);
                string pass = parser.getStr(MyAccount::namePassword);
                MyAccount acc;
                acc.login = nick;
                acc.password = pass;
                acc.id = 5;
                Reply r("", 0, 2, acc.encode());
                tmp = r.encode() + "\r\n";
                break;
            }
            case (3): {
                Parser parser;
                parser.setJson(q.body);
                int id = parser.getInt(MyAccount::nameId);
                vector<ChatInfo> arr;
                arr.emplace_back(3, "beseda1");
                arr.emplace_back(5, "lesteh");
                parser.clear();
                vector<string> jsons;
                for(const auto & item: arr) {
                    jsons.push_back(item.encode());
                }
                parser.addInt(id,MyAccount::nameId);
                parser.addArrCustom(jsons, ChatInfo::nameChatList);
                Reply r("", 0, 3, parser.getRes());
                tmp = r.encode() + "\r\n";
                break;
            }

        }

        std::copy(tmp.begin(), tmp.end(), write_buffer_);
        sock_.async_write_some( buffer(write_buffer_, tmp.size()),
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

using boost::asio::ip::tcp;

class server  {
public: server(boost::asio::io_service& io_service)
            : io_service_(io_service), acceptor_(io_service,ep) {
        connection::ptr new_connection = connection::new_();
        acceptor_.async_accept(new_connection->sock(),
                               boost::bind(&server::handle_accept, this, new_connection,
                                           boost::asio::placeholders::error));

    }
    typedef boost::shared_ptr<server> ptr;
    static ptr create() {
        return ptr(new server(service));
    }
private:
    void handle_accept(const connection::ptr& new_connection,
                       const boost::system::error_code & error) {
        if (!error) {
            new_connection->start();
            connection::ptr new_connection2 = connection::new_();
            acceptor_.async_accept(new_connection2->sock(),
                                   boost::bind(&server::handle_accept, this, new_connection2,
                                               boost::asio::placeholders::error));
        }

    }

private:
    boost::asio::io_service &io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
};

int main(int argc, char* argv[]) {
    server::ptr server = server::create();
    service.run();
}