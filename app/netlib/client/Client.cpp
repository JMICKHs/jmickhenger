#include "Client.h"

ba::io_service Client::service = ba::io_service();
optional<shared_ptr<Client>> Client::single = nullopt;
