//
// Created by Sergei Alexeev on 15.04.2020.
//

#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include <cstdlib>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <queue>
#include <optional>
#include <utility>
#include <functional>

using boost::asio::ip::tcp;
namespace ba = boost::asio;
using namespace std;

class Client: public enable_shared_from_this<Client> {
public:
    Client(const Client &other) = delete;
    Client(Client &&other) = delete;
    Client& operator=(const Client &other) = delete;
    Client& operator=(Client &&other) = delete;
    static shared_ptr<Client> shared() {
        if (!single) {
            tcp::resolver resolver(service);
            auto eit = resolver.resolve({"127.0.0.1", "8000"});
            single = shared_ptr<Client>(new Client(eit));
//            boost::asio::socket_base::keep_alive option(true);
//            single.value()->sock.set_option(option);
        }
        return single.value();
    }
    void run() {
        connect(eit);
        t = thread([self = shared_from_this()](){
            self->service.run();
        });
    }
    void write(const string & msg) {
        auto handler = [self = shared_from_this(), msg]() {
            bool key = !self->writeMsgQue.empty();
            self->writeMsgQue.push(msg);
            if (!key) {
                self->writeFromQue();
            }
        };
        service.post(handler);
    }
    void close() {
        auto handler = [self = shared_from_this()]() {
            self->sock.close();
        };
        service.post(handler);
        t.join();
    }
    void setMsgHandler(const function<void(const string &)> & f) {
        msgHandler = f;
    }
private:
    Client(tcp::resolver::iterator & endpointIterator): sock(service) {
//        ba::socket_base::keep_alive option(true);
//        sock.set_option(option);
        eit = endpointIterator;
    }
    void connect(tcp::resolver::iterator & it) {
        auto handler = [self = shared_from_this()](boost::system::error_code err, const tcp::resolver::iterator& it) {
            if (!err) {
                //отправка init сообщения
                self->loopRead();
            } else {
                cout << err.value() << endl;
            }
        };
        ba::async_connect(sock, std::move(it), handler);
    }
    void loopRead() {
        auto buf = ba::buffer(readMsg);
        auto condition = boost::bind(&Client::readСondition, shared_from_this(), _1, _2);
        auto handler = [self = shared_from_this()](boost::system::error_code err, size_t length) {
            if (!err) {
                string msg;
//                msg.resize(length);
                //msg.reserve(length - 3);
//                copy((self->readMsg).begin(), (self->readMsg).end() - 4, msg.begin());
                //copy(self->readMsg.begin(), self->readMsg.end() - 3, msg.begin());
                for(size_t i = 0; i < length - 3; ++i) {
                    msg.push_back(self->readMsg[i]);
                }
                if(self->msgHandler) {
                    self->msgHandler.value()(msg);
                } else {
                    cout << "not handler str \n";
                }
                self->loopRead();
            } else {
                cout << err.value() << endl;
            }
        };
        ba::async_read(sock, buf, condition, handler);
    }
    bool readСondition(const boost::system::error_code & err, size_t length) {
        if (err) return false;
        bool key = readMsg[length - 2] == '\r' && readMsg[length - 1] == '\n'; // в конце \r\n
        return key;
    }

    void writeFromQue() {
        auto buf = ba::buffer(writeMsgQue.front().data(),writeMsgQue.front().size());
        auto handler = [self = shared_from_this()](boost::system::error_code err, std::size_t length) {
            if (!err) {
                self->writeMsgQue.pop();
                if (!self->writeMsgQue.empty()) {
                    self->writeFromQue();
                }
            }
            else {
                cout << err.value() << endl;
                self->sock.close();
            }
        };
        ba::async_write(sock, buf, handler);
    }
private:
    std::thread t;
    static ba::io_service service;
    tcp::socket sock;
    tcp::resolver::iterator eit;
    enum { maxMsg = 2048 };
    array<char, maxMsg> readMsg;
    queue<string> writeMsgQue;
    optional<function<void(const string &)>> msgHandler;
    static optional<shared_ptr<Client>> single;
};

ba::io_service Client::service = ba::io_service();
optional<shared_ptr<Client>> Client::single = nullopt;


#endif //NETWORK_CLIENT_H
