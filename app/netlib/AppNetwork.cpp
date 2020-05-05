//
// Created by Sergei Alexeev on 05.05.2020.
//

#include "AppNetwork.h"

optional<shared_ptr<AppNetwork>> AppNetwork::single = nullopt;

AppNetwork::AppNetwork() {
    announcer = unique_ptr<Announcer>(new Announcer);
    cache = unique_ptr<AbstractCache>(new Cache);
    client = Client::shared();
    client->run();
}

shared_ptr<AppNetwork> AppNetwork::shared() {
    if(!single) {
        single = shared_ptr<AppNetwork>(new AppNetwork);
    }
    return single.value();
}
