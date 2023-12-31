#ifndef PLT_LIVEGAME_H
#define PLT_LIVEGAME_H

#include "state.h"
#include "engine.h"
#include "Client.h"
#include "CommandQueue.h"

namespace server {
    class LiveGame {
    private:
        LiveGame();
        state::GameState *game;
        engine::Engine *eng;
        CommandQueue distributedCommands;
        std::vector<Client> players;
    public:
        ~LiveGame();
        string handlePlayerJoin(const string& playerName);
        void addCommand(const string& command);
        static LiveGame& getInstance();
        state::GameState* getState();
        string retrieveCommands(const string& playerName);
    };
}
#endif
