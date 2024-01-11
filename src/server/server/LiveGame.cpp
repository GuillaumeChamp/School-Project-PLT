//
// Created by guillaume on 12/31/23.
//

#include "LiveGame.h"

#include <algorithm>
#include <sstream>
#include <iterator>

using namespace server;

LiveGame::LiveGame() {
    this->game = nullptr;
    this->eng = nullptr;
}

LiveGame &LiveGame::getInstance() {
    static LiveGame inst{};
    return inst;
}

void LiveGame::addCommand(const std::string& command) {
    distributedCommands.addCommand(command);
    //TODO : create command using an engine util method
    auto *command1 = new engine::Command();
    eng->addCommand(command1);
    eng->executeAllCommands();
}

std::string LiveGame::handlePlayerJoin(const std::string& playerName) {
    // handle game full
    if (players.size() >= 4) {
        return "This game is full\r\n";
    }
    // find if player exist
    for (const auto& p: players) {
        if (p.getClientName() == playerName) {
            return "You are already in the game\r\n";
        }
    }

    players.emplace_back(playerName, static_cast<state::PlayerId>(players.size() + 1));
    if (players.size() == 4) {
        this->game = new state::GameState{players[0].getClientName(), players[1].getClientName(),
                                          players[2].getClientName(), players[3].getClientName()};
        this->eng = std::addressof(engine::Engine::getInstance());
        //TODO use start game command
        return "OK, game is starting.\r\n";

    }
    return "OK\r\n";

}

state::GameState *LiveGame::getState() {
    return game;
}

std::string LiveGame::retrieveCommands(const std::string& playerName) {
    for (auto p: players) {
        if (p.getClientName() == playerName) {
            auto commandList = distributedCommands.retrieveCommands(p.getLastUpdate());
            p.updateTimestamp(std::chrono::high_resolution_clock::now());
            std::ostringstream vts;
            if (commandList.empty()){
                return {};
            }
            // Convert all but the last element to avoid a trailing
            std::copy(commandList.begin(), commandList.end()-1,std::ostream_iterator<std::string>(vts, ";"));

            // Now add the last element with no delimiter
            vts << commandList.back();
            return vts.str();
        }
    }
    return {};
}

LiveGame::~LiveGame() {
    this->players.clear();
}
