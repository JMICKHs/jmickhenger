//
// Created by nick on 02.05.2020.
//

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Connection.h"
#define MEM_FN2(x,y,z)  boost::bind(&self_type::x, shared_from_this(),y,z)
#define MEM_FN1(x,y)  boost::bind(&self_type::x, shared_from_this(),y)
using boost::asio::ip::tcp;

tcp::socket &Connection::socket() {
    return socket_;
}

void Connection::start() {
    boost::asio::async_read(socket_,
                            boost::asio::buffer(nickname_, nickname_.size()),
                            boost::bind(&Connection::readCondition, shared_from_this(), _1, _2),
                            strand_.wrap(boost::bind(&Connection::name_handler, shared_from_this(), _1)));
}

void Connection::on_message(std::array<char, MAX_IP_PACK_SIZE> &msg) {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress) {
        boost::asio::async_write(socket_,
                                 boost::asio::buffer(write_msgs_.front(), write_msgs_.front().size()),
                                 strand_.wrap(boost::bind(&Connection::write_handler, shared_from_this(), _1)));
    }
}

void Connection::name_handler(const boost::system::error_code &error) {
    std::cout << nickname_.data();
//    тут магия с id_number будет
    room_.enter(shared_from_this(), std::string(nickname_.data()));

    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_,read_msg_.size()),
                            boost::bind(&Connection::readCondition, shared_from_this(), _1, _2),

                            strand_.wrap(boost::bind(&Connection::read_handler, shared_from_this(), _1)));
}
bool Connection::readCondition(const boost::system::error_code &err, size_t length) {
    if (err) return false;
    bool key = read_msg_[length - 2] == '\r' && read_msg_[length - 1] == '\n'; // в конце \r\n
    return key;
}

void Connection::read_handler(const boost::system::error_code &error) {
    if (!error) {
        room_.mailing(read_msg_, shared_from_this());
//вот тут он тип перманентно должен делать считывание из блядской очереди сообщений
//а не тригериться только когда в очереди появляется что-то
//хотя
//если челик что-то захуярил в смс
//мы ставим это в очередь к бд
//быстро
        boost::asio::async_read(socket_,
                                boost::asio::buffer(read_msg_,read_msg_.size()),
                                boost::bind(&Connection::readCondition, shared_from_this(), _1, _2),

                                strand_.wrap(boost::bind(&Connection::read_handler, shared_from_this(), _1)));
    }
    else {
        room_.leave(shared_from_this());
    }
}

void Connection::write_handler(const boost::system::error_code &error) {
    if (!error)
    {
        write_msgs_.pop_front();

        if (!write_msgs_.empty())
        {
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(write_msgs_.front(), write_msgs_.front().size()),
                                     strand_.wrap(boost::bind(&Connection::write_handler, shared_from_this(), _1)));
        }
    }
    else
    {
        room_.leave(shared_from_this());
    }
}
