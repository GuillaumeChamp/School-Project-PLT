// Engine.cpp
#include "Engine.h"
#include <thread>

namespace engine {
    Engine::Engine(state::GameState &state) : currentState(state) {
    }

    // Destructor
    Engine::~Engine() = default;

    void Engine::addCommand(Command *cmd) {
        listOfCommands.push_back(cmd);
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

    void Engine::init(state::GameState &state) {
        getInstanceImpl(&state);
    }

    void Engine::startThread() {
        std::thread thread1([this]() {
            while (true) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                if (!this->listOfCommands.empty()){
                    this->executeAllCommands();
                }
            }
        });
        thread1.detach();
    }

    engine::Engine &Engine::getInstance() {
        return getInstanceImpl();
    }

    Engine &Engine::getInstanceImpl(state::GameState *const state) {
        static Engine instance{*state};
        return instance;
    }

}
