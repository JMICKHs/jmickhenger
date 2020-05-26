#include "Client.h"

#import <fstream>
#import <cassert>
#import <sstream>

using boost::asio::ip::tcp;
namespace ba = boost::asio;
using namespace std;

ba::io_service Client::service = ba::io_service();
boost::asio::ssl::context Client::ctx = boost::asio::ssl::context(boost::asio::ssl::context::sslv23);
std::string Client::endMsg = "\r\n";

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
    sslSock.set_verify_mode(boost::asio::ssl::verify_peer);
    ctx.load_verify_file("../netlib/certificates/server.crt");
    sslSock.set_verify_callback(boost::bind(&Client::verifyCertificate, shared_from_this(), _1, _2));
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
        self->writeMsgQue.push(msg + endMsg);
        if (!key) {
            self->writeFromQue();
        }
    };
    service.post(handler);
}

void Client::close() {
    auto handler = [self = shared_from_this()]() {
        self->sslSock.lowest_layer().close();
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

Client::Client(): sslSock(service, ctx) {}

void Client::connect(tcp::resolver::iterator &it) {
    auto handler = boost::bind(&Client::handleConnect, shared_from_this(), boost::asio::placeholders::error);
    ba::async_connect(sslSock.lowest_layer(), it, handler);
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
                cout << "not handler str\n";
            }
            self->loopRead();
        } else {
            self->handleErr(err);
        }
    };
    ba::async_read_until(sslSock, bufRead, endMsg, handler);
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
            self->handleErr(err);
        }
    };
    ba::async_write(sslSock, buf, handler);
}

bool Client::verifyCertificate(bool preverified, boost::asio::ssl::verify_context& ctx) {
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    return preverified;
}

void Client::handleConnect(const boost::system::error_code &error) {
    auto handler = [self = shared_from_this()](const boost::system::error_code& err) {
        if (!err) {
            self->loopRead();
        } else {
            self->handleErr(err);
        }
    };

    if (!error) {
        sslSock.async_handshake(boost::asio::ssl::stream_base::client, handler);
    }
    else {
        handleErr(error);
    }
}

void Client::handleErr(const boost::system::error_code &error) {
    if (errHandler) {
        errHandler.value()(error.value());
    } else {
        cout << "err in connect " << error.message() << endl;
        close();
    }
}
