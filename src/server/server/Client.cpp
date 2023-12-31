//
// Created by guillaume on 12/31/23.
//
#include "Client.h"

using namespace server;
Client::Client(std::string name,state::PlayerId id) {
    this->clientName = name;
    this->playerId = id;
    this->lastUpdate = high_resolution_clock::now();
}

state::PlayerId server::findPlayer(std::vector<Client> &clientList, std::string name) {
    for (auto c : clientList){
        if (c.clientName==name){
            return c.playerId;
        }
    }
    return state::NO_PLAYER;
}

const std::string &Client::getClientName() const {
    return clientName;
}

state::PlayerId Client::getPlayerId() const {
    return playerId;
}

const time_point<high_resolution_clock> &Client::getLastUpdate() const {
    return lastUpdate;
}

void Client::updateTimestamp(const time_point<high_resolution_clock> &lastUpdate) {
    this->lastUpdate=lastUpdate;
}
