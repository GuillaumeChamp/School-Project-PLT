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
    engine::Command* command1 = new engine::Command();
    eng->addCommand(command1);
    eng->executeAllCommands();
}

string LiveGame::handlePlayerJoin(std::string playerName) {
    state::PlayerId playerId = findPlayer(players,playerName);
    if (players.size()>=4){
        return "This game is full\r\n";
    }
    if (playerId==state::NO_PLAYER){
        players.emplace_back(playerName,static_cast<state::PlayerId>(players.size()+1));
        return "OK\r\n";
    }
    return "You are already in the game\r\n";
}

state::GameState *LiveGame::getState() {
    return game;
}

string LiveGame::retrieveCommands(string playerName) {
    for (auto p : players){
        if(p.getClientName()==playerName){
            distributedCommands.retrieveCommands(p.getLastUpdate());
        }
    }
    return std::string();
}

LiveGame::~LiveGame() {
    this->players.clear();
}
