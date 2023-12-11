// Command.cpp
#include "Command.h"

namespace engine {

    // Constructor
    Command::Command() = default;

    // Destructor
    Command::~Command() = default;

    // Getter for CommandTypeId
    CommandTypeId Command::getCommandTypeId() {
        return commandTypeId;
    }

    // Execute method
    void Command::execute(state::GameState &state) {
    }

    // Serialize method
    void Command::serialize() {}

    bool Command::check(state::GameState &state) {
        return authorPlayer==state.playing;
    }


} // namespace engine
