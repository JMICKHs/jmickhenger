//
// Created by nick on 15.04.2020.
//
#include "Source/Server/Server.h"


int main(int argc, char* argv[]) {
    Server::ptr server = Server::create();
    server->run_server();
    service.run();
}