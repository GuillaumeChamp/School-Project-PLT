#include "Engine.h"
#include "Command.h"

namespace engine {

  // Constructor with parameter
  Engine::Engine(state::GameState state) : currentState(state) {
    // Other initialization if needed
    init();
  }

  // Destructor
  Engine::~Engine() {
    // Clean up resources if needed
  }

  // Initialization method
  void Engine::init() {
    std::vector<std::shared_ptr<Command>> commandList;
  }

  // Getter for the current game state
  state::GameState Engine::getState() {
    return currentState;
  }

  // Method to add a command to the engine
  void Engine::addCommand(std::shared_ptr<Command> cmd) {

    listOfCommands.push_back(cmd);
    
    
  }

} // namespace engine
