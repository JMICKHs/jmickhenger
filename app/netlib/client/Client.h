//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_CLIENT_H
#define NETLIB_CLIENT_H

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
#include <mutex>

using boost::asio::ip::tcp;
namespace ba = boost::asio;
using namespace std;

class AbstractClient {
public:
    virtual void run() = 0;
    virtual void write(const string & msg) = 0;
    virtual void close() = 0;
    virtual void setMsgHandler(const function<void(const string &)> & f) = 0;
    virtual void setErrHandler(const function<void(int)> & f) = 0;
};

class Client: public enable_shared_from_this<Client>, public AbstractClient {
public:
    Client(const Client &other) = delete;
    Client(Client &&other) = delete;
    Client& operator=(const Client &other) = delete;
    Client& operator=(Client &&other) = delete;
    static shared_ptr<Client> shared();
    void run() override;
    void write(const string & msg) override;
    void close() override;
    void setMsgHandler(const function<void(const string &)> & f) override;
    void setErrHandler(const function<void(int)> & f) override;
private:
    explicit Client(tcp::resolver::iterator & endpointIterator);
    void connect(tcp::resolver::iterator & it);
    void loopRead();
    bool readСondition(const boost::system::error_code & err, size_t length);
    void writeFromQue();
private:
    std::thread t;
    static std::mutex mtx;
    static ba::io_service service;
    tcp::socket sock;
    tcp::resolver::iterator eit;
    enum { maxMsg = 2048 };
    array<char, maxMsg> readMsg;
    queue<string> writeMsgQue;
    optional<function<void(const string &)>> msgHandler;
    optional<function<void(int)>> errHandler;
    static optional<shared_ptr<Client>> single;
};


#endif //NETLIB_CLIENT_H
