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
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 20f2d65 (MERCILESPTR)
  void Engine::addCommand (std::unique_ptr<Command> cmd){

    listOfCommands.push_back(std::move(cmd));

  }
<<<<<<< HEAD
=======
  void addCommand (std::vector<std::unique_ptr<Command>> cmd){}
>>>>>>> 6cf1432 (ComprendsRien)

  void Engine::executeAllCommands(state::GameState state){
    for (auto& cmd : listOfCommands) {
    cmd->execute(state);
  }
  }
  // Setters and Getters
  // You can add setters and getters for other attributes as needed
=======
>>>>>>> 20f2d65 (MERCILESPTR)

  // Setters and Getters
  // You can add setters and getters for other attributes as needed

} // namespace engine
