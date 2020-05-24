#include "Client.h"

#import <fstream>
#import <cassert>
#import <sstream>

using boost::asio::ip::tcp;
namespace ba = boost::asio;
using namespace std;

ba::io_service Client::service = ba::io_service();

optional<pair<string, string>> getHostFromConfig() {
    static string fileConfig = "../netlib/configs/clientConfig";
    static string ipKey = "IP:";
    static string portKey = "PORT:";
    pair<string, string> result;
    ifstream conf(fileConfig);
    string line;
    getline(conf, line);
    if(line == ipKey) {
        getline(conf, line);
        result.first = line;
    } else {
        return nullopt;
    }
    getline(conf, line);
    if(line == portKey) {
        getline(conf, line);
        result.second = line;
    } else {
        return nullopt;
    }
    return result;
}

shared_ptr<Client> Client::shared()  {
    static shared_ptr<Client> single(new Client);
    return single;
}

void Client::run() {
    auto host = getHostFromConfig();
    tcp::resolver resolver(service);
    assert(host && "config неправильно заполнен"); //assert тут для того, чтобы во время разработки не ломать голову
    // где же крашнулось. В проде assert никогда не сработает
    eit = resolver.resolve({host.value().first, host.value().second});
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

Client::Client(): sock(service) {}

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
    auto handler = [self = shared_from_this()](boost::system::error_code err, size_t length) {
        if (!err) {
            std::ostringstream out;
            out << &(self->bufRead);
            string msg = out.str();
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
    ba::async_read_until(sock, bufRead, "\r\n", handler);
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