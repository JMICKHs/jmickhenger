//
// Created by nick on 15.04.2020.
//
#include "Source/Server/Server.h"


#include <boost/asio.hpp>
#include "Source/Connection/Connection.h"
#include <boost/thread/thread.hpp>
#include <thread>
#include <mutex>
#include "Source/Server/WorkerThread.h"

using boost::asio::ip::tcp;






//----------------------------------------------------------------------

int main(int argc, char* argv[]) {

       // DBWorker a("Users");
       // a.AddInt("_id", 0);
       // a.AddInt("counter", 0);
       // a.SaveDoc();
       // a.ChangeCollection("Info");
       // a.AddInt("_id", 0);
       // a.AddInt("last_chat_id", 0);
       // a.SaveDoc();
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: chat_Server <port> [<port> ...]\n";
            return 1;
        }

        std::shared_ptr<boost::asio::io_service> io_service(new boost::asio::io_service);
        boost::shared_ptr<boost::asio::io_service::work> work(new boost::asio::io_service::work(*io_service));
        boost::shared_ptr<boost::asio::io_service::strand> strand(new boost::asio::io_service::strand(*io_service));

        std::cout << "[" << std::this_thread::get_id() << "]" << "Server starts" << std::endl;

        std::list <std::shared_ptr<Server>> Servers;
        for (int i = 1; i < argc; ++i)
        {
            tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
            std::shared_ptr<Server> a_Server(new Server(*io_service, *strand, endpoint));
            Servers.push_back(a_Server);
        }

        boost::thread_group workers;
        for (int i = 0; i < 1; ++i)
        {
            boost::thread * t = new boost::thread{ boost::bind(&worker_thread::run, io_service) };

#ifdef __linux__
            // bind cpu affinity for worker thread in linux
            cpu_set_t cpuset;
            CPU_ZERO(&cpuset);
            CPU_SET(i, &cpuset);
            pthread_setaffinity_np(t->native_handle(), sizeof(cpu_set_t), &cpuset);
#endif
            workers.add_thread(t);
        }

        workers.join_all();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}



//{"cmd": "2","body": {"login": "kek","password": "123"}}