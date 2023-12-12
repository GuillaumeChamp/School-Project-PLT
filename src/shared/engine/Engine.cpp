// Engine.cpp
#include "Engine.h"
#include "Command.h"


namespace engine {

    // Constructor with parameter
    Engine::Engine(state::GameState &state) : currentState(state) {
        // Other initialization if needed
        init();
    }

    // Destructor
    Engine::~Engine() = default;

    // Initialization method
    void Engine::init() {
        // Perform initialization tasks here
    }

    // Add a command to the list of commands

    void Engine::addCommand(Command *cmd) {
        listOfCommands.push_back(cmd);
    }


    void Engine::executeAllCommands() {
        //execute all the commands but check before
        for (Command *command: listOfCommands) {
            if (command->check(this->currentState)) {
                command->execute(this->currentState);
            }
        }
        //free the memory
        for (auto p: listOfCommands){
            delete p;
        }
        listOfCommands.clear();
    }

    Engine* Engine::getInstance(state::GameState &state){
        if (!INSTANCE) {
            INSTANCE = new Engine(state);
        }
        return INSTANCE;
    }

    Engine* Engine::INSTANCE = nullptr;

} // namespace engine
