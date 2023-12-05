// Engine.cpp
#include "Engine.h"
#include "Command.h"

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
    
    // Perform initialization tasks here
  }

  // Getter for the current game state
  state::GameState Engine::getState() {
    return currentState;
  }

  // Add a command to the list of commands
  
  void Engine::addCommand (Command& cmd){

    listOfCommands.push_back(cmd);

  }


  void Engine::executeAllCommands(state::GameState state){
    for (auto& cmd : listOfCommands) {
    cmd.execute(state);
  }
  }


  // Setters and Getters
  // You can add setters and getters for other attributes as needed

} // namespace engine
