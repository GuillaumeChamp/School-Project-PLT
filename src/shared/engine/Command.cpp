// Command.cpp
#include "Command.h"

namespace engine {

  // Constructor
  Command::Command() {
    // Initialize attributes as needed
  }
  // Destructor
  Command::~Command() {}

  // Getter for CommandTypeId
  CommandTypeId Command::getCommandTypeId() {
    return commandTypeId;
  }

  // Execute method
  void Command::execute(state::GameState state) {
    // Implement the logic to execute the command on the game state
    // You may use the 'playing' and 'card' attributes in this method
  }

  // Serialize method
  void Command::serialize() {
    // Implement the logic to serialize the command
    // You may want to output information about 'commandTypeId', 'playing', and 'card'
  }

  

  // Setters and Getters
  // You can add implementations for setters and getters as needed

} // namespace engine
