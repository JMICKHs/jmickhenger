//
// Created by Sergei Alexeev on 15.04.2020.
//

#include "Client.h"

ba::io_service Client::service = ba::io_service();
optional<shared_ptr<Client>> Client::single = nullopt;