// Command.cpp
#include "Command.h"

namespace engine {

  // Constructor
  Command::Command() {
  }
  // Destructor
  Command::~Command() {}

  // Getter for CommandTypeId
  CommandTypeId Command::getCommandTypeId() {
    return commandTypeId;
  }

  // Execute method
  void Command::execute(state::GameState state) {
  }

  // Serialize method
  void Command::serialize() {
<<<<<<< HEAD
=======
    // Implement the logic to serialize the command
    // You may want to output information about 'commandTypeId', 'playing', and 'card'
>>>>>>> 20f2d65 (MERCILESPTR)
  }

  
} // namespace engine
