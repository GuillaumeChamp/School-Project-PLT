// Engine.cpp
#include "Engine.h"
#include <thread>

namespace engine {
    Engine::Engine(state::GameState &state) : currentState(state) {
        // Other initialization if needed
        init();
    }

    // Destructor
    Engine::~Engine()= default;

    void Engine::init() {
        // Perform initialization tasks here
    }

    void Engine::addCommand(Command *cmd) {
        listOfCommands.push_back(cmd);
        executeAllCommands();
    }

    void Engine::executeAllCommands() {
        //execute all the commands but check before
        for (Command *command: listOfCommands) {
            if (command->check(currentState)) {
                command->execute(currentState);
            }
        }
        //free the memory with processed command
        for (auto p: listOfCommands) {
            delete p;
        }
        listOfCommands.clear();
    }

    Engine & Engine::getInstance(state::GameState &state) {
        static Engine inst{state};
        return inst;
    }

    void Engine::startThread() {
        std::thread thread1([this]() {
            while (this->currentState.getGamePhase()!=state::END_GAME) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                if (!this->listOfCommands.empty()){
                    this->executeAllCommands();
                }
            }
        });
        thread1.detach();
    }

}
