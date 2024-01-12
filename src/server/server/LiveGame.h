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
        CommandQueue distributedCommands;
        std::vector<Client> players;
    public:
        /**
         * Singleton get
         * @return the unique instance.
         */
        static LiveGame &getInstance();

        ~LiveGame();

        /**
         * Add a new player to the game.
         * @param playerName player name.
         * @return a string holding ok if successfully add or an error message.
         */
        string handlePlayerJoin(const string &playerName);

        /**
         * Add a command to the engine if the game is live.
         * Not holding error because api already check.
         * @param command the command as a string that need to be parsed by a command parser.
         */
        void addCommand(const string &command);
        //getter
        state::GameState *getState();
        /**
         * Retrieve all the commands the player don't have.
         * @param playerName name of the player who want to update.
         * @return a string that concat all the commands
         */
        string retrieveCommands(const string &playerName);
    };
}
#endif
