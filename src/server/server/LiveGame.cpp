//
// Created by guillaume on 12/31/23.
//

#include "LiveGame.h"

using namespace server;

LiveGame::LiveGame() {
    this->game = nullptr;
    this->eng = nullptr;
}

LiveGame &LiveGame::getInstance() {
    static LiveGame inst{};
    return inst;
}

void LiveGame::addCommand(std::string command) {
    distributedCommands.addCommand(command);
    //TODO : create command using an engine util method
    engine::Command *command1 = new engine::Command();
    eng->addCommand(command1);
    eng->executeAllCommands();
}

string LiveGame::handlePlayerJoin(std::string playerName) {
    // handle game full
    if (players.size() >= 4) {
        return "This game is full\r\n";
    }
    // find if player exist
    state::PlayerId playerId = state::NO_PLAYER;
    for (auto p: players) {
        if (p.getClientName() == playerName) {
            return "You are already in the game\r\n";
        }
    }

    players.emplace_back(playerName, static_cast<state::PlayerId>(players.size() + 1));
    if (players.size() == 4) {
        this->game = new state::GameState{players[0].getClientName(), players[1].getClientName(),
                                          players[2].getClientName(), players[3].getClientName()};
        this->eng = std::addressof(engine::Engine::getInstance(*game));
        //TODO use start game command
        return "OK, game is starting.\r\n";

    }
    return "OK\r\n";

}

state::GameState *LiveGame::getState() {
    return game;
}

string LiveGame::retrieveCommands(string playerName) {
    for (auto p: players) {
        if (p.getClientName() == playerName) {
            distributedCommands.retrieveCommands(p.getLastUpdate());
            p.updateTimestamp(std::chrono::high_resolution_clock::now());
        }
    }
    return std::string();
}

LiveGame::~LiveGame() {
    this->players.clear();
}
