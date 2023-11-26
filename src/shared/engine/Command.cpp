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

  }

  
} // namespace engine
