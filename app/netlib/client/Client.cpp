#include "Client.h"


using boost::asio::ip::tcp;
namespace ba = boost::asio;
using namespace std;

ba::io_service Client::service = ba::io_service();

shared_ptr<Client> Client::shared()  {
    static shared_ptr<Client> single(new Client(service));
    return single;
}

void Client::run() {
    connect(eit);
    t = thread([self = shared_from_this()](){
        self->service.run();
    });
}

void Client::write(const string &msg) {
    auto handler = [self = shared_from_this(), msg]() {
        bool key = !self->writeMsgQue.empty();
        self->writeMsgQue.push(msg + "\r\n");
        if (!key) {
            self->writeFromQue();
        }
    };
    service.post(handler);
}

void Client::close() {
    auto handler = [self = shared_from_this()]() {
        self->sock.close();
    };
    service.post(handler);
    t.join();
}

void Client::setMsgHandler(const function<void(const string &)> &f) {
    msgHandler = f;
}

void Client::setErrHandler(const function<void(int)> &f) {
    errHandler = f;
}

Client::Client(ba::io_service & service): sock(service) {
    tcp::resolver resolver(service);
    eit = resolver.resolve({"23.111.202.91", "8841"});
}

void Client::connect(tcp::resolver::iterator &it) {
    auto handler = [self = shared_from_this()](boost::system::error_code err, const tcp::resolver::iterator& it) {
        if (!err) {
            self->loopRead();
        } else {
            if (self->errHandler) {
                self->errHandler.value()(err.value());
            } else {
                cout << "err in connect " << err.value() << endl;
                self->close();
            }
        }
    };
    ba::async_connect(sock, std::move(it), handler);
}

void Client::loopRead() {
    memset(readMsg.data(), '\0', maxMsg);
    auto buf = ba::buffer(readMsg);
    auto condition = boost::bind(&Client::readCondition, shared_from_this(), _1, _2);
    auto handler = [self = shared_from_this()](boost::system::error_code err, size_t length) {
        if (!err) {
            string msg; msg.reserve(length);
            for(size_t i = 0; i < length - 2; ++i) {
                msg.push_back(self->readMsg[i]);
            }
            if(self->msgHandler) {
                self->msgHandler.value()(msg);
            } else {
                cout << "not handler str \n";
            }
            self->loopRead();
        } else {
            if (self->errHandler) {
                self->errHandler.value()(err.value());
            } else {
                cout << "err in connect " << err.value() << endl;
                self->close();
            }
        }
    };
    ba::async_read(sock, buf, condition, handler);
}

bool Client::readCondition(const boost::system::error_code &err, size_t length) {
    if (err) return false;
    bool key = readMsg[length - 2] == '\r' && readMsg[length - 1] == '\n'; // в конце \r\n
    return key;
}

void Client::writeFromQue() {
    auto buf = ba::buffer(writeMsgQue.front().data(),writeMsgQue.front().size());
    auto handler = [self = shared_from_this()](boost::system::error_code err, std::size_t length) {
        if (!err) {
            self->writeMsgQue.pop();
            if (!self->writeMsgQue.empty()) {
                self->writeFromQue();
            }
        }
        else {
            if (self->errHandler) {
                self->errHandler.value()(err.value());
            } else {
                cout << "err in connect " << err.value() << endl;
                self->close();
            }
        }
    };
    ba::async_write(sock, buf, handler);
}


