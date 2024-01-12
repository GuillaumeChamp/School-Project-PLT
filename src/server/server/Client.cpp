//
// Created by guillaume on 12/31/23.
//
#include "Client.h"

#include <utility>

using namespace server;
Client::Client(std::string name,state::PlayerId id) {
    this->clientName = std::move(name);
    this->playerId = id;
    this->lastUpdate = high_resolution_clock::now();
}

const std::string &Client::getClientName() const {
    return clientName;
}

const time_point<high_resolution_clock> &Client::getLastUpdate() const {
    return lastUpdate;
}

void Client::updateTimestamp(const time_point<high_resolution_clock> &lastUpdate) {
    this->lastUpdate=lastUpdate;
}

Client::~Client() = default;