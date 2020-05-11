#include "Client.h"

ba::io_service Client::service = ba::io_service();
optional<shared_ptr<Client>> Client::single = nullopt;
std::mutex Client::mtx = std::mutex();

shared_ptr<Client> Client::shared()  {
    if (!single) {
        mtx.lock();
        tcp::resolver resolver(service);
        auto eit = resolver.resolve({"127.0.0.1", "8000"});
        single = shared_ptr<Client>(new Client(eit));
        mtx.unlock();
    }
    return single.value();
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

Client::Client(tcp::resolver::iterator &endpointIterator) : sock(service) {
//        ba::socket_base::keep_alive option(true);
//        sock.set_option(option);
    eit = endpointIterator;
}

void Client::connect(tcp::resolver::iterator &it) {
    auto handler = [self = shared_from_this()](boost::system::error_code err, const tcp::resolver::iterator& it) {
        if (!err) {
            //отправка init сообщения
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
    auto buf = ba::buffer(readMsg);
    auto condition = boost::bind(&Client::readCondition, shared_from_this(), _1, _2);
    auto handler = [self = shared_from_this()](boost::system::error_code err, size_t length) {
        if(!(self->sock.is_open())) {
            self->close();
        }
        if (!err) {
            string msg; msg.reserve(length - 3);
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
    if (err || !sock.is_open()) return ;
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


