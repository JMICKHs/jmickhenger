//
// Created by nick on 15.04.2020.
//


#include "BusinessLogicProxy.h"
#include <boost/bind.hpp>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <boost/asio/streambuf.hpp>

using namespace std::chrono_literals;


void BusinessLogicProxy::enter(std::shared_ptr<abstract_Connection> abstract_Connection, const std::string &nickname) {
    connections_.insert(abstract_Connection);
    id_collection[negative_id] = abstract_Connection;
    std::cout << "Добавили коннект neg_id" << negative_id << std::endl;
    negative_id--;
}

void BusinessLogicProxy::leave(std::shared_ptr<abstract_Connection> abstract_Connection) {
    connections_.erase(abstract_Connection);
}

void BusinessLogicProxy::mailing(boost::asio::streambuf &msg,
                                   std::shared_ptr<abstract_Connection> abstract_Connection) {

    std::array<char, MAX_IP_PACK_SIZE> formatted_msg = {};
    std::string formatted_string;
    auto string_to_bd = std::string();
    int i = 0;

    auto msg_to_string = std::make_shared<std::string>();
    auto out = std::make_shared<std::ostringstream>();
    *out << &msg;
    *msg_to_string =(*out).str();
    *msg_to_string += "\r\n";

    char *id_begin =  strstr((*msg_to_string).data(), "id: ");
    char *auth_begin =  strstr((*msg_to_string).data(), "auth: ");
    char *test_begin =  strstr((*msg_to_string).data(), "test: ");

    if (id_begin == (*msg_to_string).data()) {
        int connection_number = atoi(id_begin + 4);
        std::cout << "new id is " << connection_number <<std::endl;
        auto prev = id_collection.find(connection_number);
        if (prev == id_collection.end()) {
//                если не нашли такого id, значит он заходит в первый раз
//                вставляем его в мапу
            alive_users_id.push_back(connection_number);
            id_collection[connection_number] = abstract_Connection;
        } else {
            id_collection.erase(prev);
            id_collection[connection_number] = abstract_Connection;
        }



    } else if (auth_begin == (*msg_to_string).data()) {
        std::cout << "user_name: " << (auth_begin + 6) << std::endl;
    } else if (test_begin == (*msg_to_string).data()) {
        std::cout << "client pings server: " << (auth_begin + 6) << std::endl;
    } else {
        while (i < msg_to_string->size() && ((*msg_to_string)[i] != '\r' || (*msg_to_string)[i+1] != '\n')) {
            string_to_bd.push_back((*msg_to_string)[i]);
            i++;
        }
        std::cout << "bd gets request : " << string_to_bd.data() << std::endl;
        int current_neg_id = negative_id + 1;

        auto ptr_to_string_to_bd = std::make_shared<std::pair<int, std::string>>(current_neg_id, string_to_bd);

        msg_queue.SetRequest(ptr_to_string_to_bd);

        int err_code; ///присвоение значения в строке 126(если логика отправила 0, то она больше не будет ничего класть в очередь)

        do {
            auto response_struct = msg_queue.GetResponse();
            std::cout << "взяли ответ у бд" << std::endl;
            int exact_connection_id = response_struct->RealId;
            int neg_connection_id = err_code = response_struct->ServerId;
            c++;
            if (c == 7) {
                int t = 0;

            std::array<char, MAX_IP_PACK_SIZE> response_msg = {};
            std::cout << "send response : " << response_struct->Json << std::endl;
            i = 0;
            while (i < response_struct->Json.size() && ((response_struct->Json)[i] != '\r' || (response_struct->Json)[i+1] != '\n')) {
                response_msg[i] = (response_struct->Json)[i];
                i++;
            }
            strcat(response_msg.data(), "\r\n");


            auto got = id_collection.find(neg_connection_id);
            if (got == id_collection.end()) {
//                если не нашли негативного id
//                тогда у пользователь авторизован и есть позитивный id
                auto exact_connection = id_collection[exact_connection_id];
                if (!exact_connection) {
                    continue;
                } else {
                    exact_connection->on_message(response_msg);
                }
            } else {
//                если есть негативный id, то
                auto exact_connection = id_collection[neg_connection_id];
                if (!exact_connection) {
                    continue;
                } else {
                    id_collection.erase(neg_connection_id);
                    exact_connection->on_message(response_msg);
                }
            }

        } while (err_code > 0);


    }
}
