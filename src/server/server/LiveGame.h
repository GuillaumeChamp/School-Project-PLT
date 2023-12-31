//
// Created by guillaume on 12/31/23.
//

#ifndef PLT_LIVEGAME_H
#define PLT_LIVEGAME_H

#include "state.h"
#include "engine.h"
#include "Client.h"
#include "CommandQueue.h"


namespace server {
    class LiveGame {
    private:
        state::GameState *game;
        engine::Engine *eng;
        CommandQueue distributedCommands;
        std::vector<Client> players;
        LiveGame();
    public:
        ~LiveGame();
        string handlePlayerJoin(string playerName);
        void addCommand(string command);
        static LiveGame& getInstance();
        state::GameState* getState();
        string retrieveCommands(string playerName);
    };
}
#endif //PLT_LIVEGAME_H
