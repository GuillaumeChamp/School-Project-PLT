//
// Created by guillaume on 12/31/23.
//
#include "Client.h"

using namespace server;
Client::Client(std::string name,state::PlayerId id) {
    this->clientName = name;
    this->playerId = id;
    this->lastUpdate = std::chrono::high_resolution_clock::now();
}

const std::string &Client::getClientName() const {
    return clientName;
}

const std::chrono::time_point<std::chrono::high_resolution_clock> &Client::getLastUpdate() const {
    return lastUpdate;
}

void Client::updateTimestamp(const std::chrono::time_point<std::chrono::high_resolution_clock> &lastUpdate) {
    this->lastUpdate=lastUpdate;
}

Client::~Client() = default;
