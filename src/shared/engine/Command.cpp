// Command.cpp
#include "Command.h"

namespace engine {

  // Constructor
  Command::Command() {
<<<<<<< HEAD
=======
    // Initialize attributes as needed
>>>>>>> 20f2d65 (MERCILESPTR)
  }
  // Destructor
  Command::~Command() {}

  // Getter for CommandTypeId
  CommandTypeId Command::getCommandTypeId() {
    return commandTypeId;
  }

  // Execute method
  void Command::execute(state::GameState state) {
<<<<<<< HEAD
=======
    // Implement the logic to execute the command on the game state
    // You may use the 'playing' and 'card' attributes in this method
>>>>>>> 20f2d65 (MERCILESPTR)
  }

  // Serialize method
  void Command::serialize() {
<<<<<<< HEAD
=======
    // Implement the logic to serialize the command
    // You may want to output information about 'commandTypeId', 'playing', and 'card'
>>>>>>> 20f2d65 (MERCILESPTR)
  }

  

<<<<<<< HEAD
=======
  // Setters and Getters
  // You can add implementations for setters and getters as needed

>>>>>>> 20f2d65 (MERCILESPTR)
} // namespace engine
