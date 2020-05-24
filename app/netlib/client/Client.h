//
// Created by Sergei Alexeev on 05.05.2020.
//

#ifndef NETLIB_CLIENT_H
#define NETLIB_CLIENT_H

#import <iostream>
#import <functional>
#import <queue>

#import <memory>
#import <optional>
#import <thread>

#import <boost/asio.hpp>
#import <boost/bind.hpp>

class AbstractClient {
public:
    virtual void run() = 0;
    virtual void write(const std::string & msg) = 0;
    virtual void close() = 0;
    virtual void setMsgHandler(const std::function<void(const std::string &)> & f) = 0;
    virtual void setErrHandler(const std::function<void(int)> & f) = 0;
};

class Client: public std::enable_shared_from_this<Client>, public AbstractClient {
public:
    Client(const Client &other) = delete;
    Client(Client &&other) = delete;
    Client& operator=(const Client &other) = delete;
    Client& operator=(Client &&other) = delete;
    static std::shared_ptr<Client> shared();
    void run() override;
    void write(const std::string & msg) override;
    void close() override;
    void setMsgHandler(const std::function<void(const std::string &)> & f) override;
    void setErrHandler(const std::function<void(int)> & f) override;
private:
    explicit Client();
    void connect(boost::asio::ip::tcp::resolver::iterator & it);
    void loopRead();
    void writeFromQue();
private:
    std::thread t;
    static boost::asio::io_service service;
    boost::asio::ip::tcp::socket sock;
    boost::asio::ip::tcp::resolver::iterator eit;
    std::queue<std::string> writeMsgQue;
    std::optional<std::function<void(const std::string &)>> msgHandler;
    std::optional<std::function<void(int)>> errHandler;
    boost::asio::streambuf bufRead;
};


#endif //NETLIB_CLIENT_H
