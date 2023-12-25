// Command.cpp
#include "Command.h"

namespace engine {

    // Constructor
    Command::Command(){
        this->targetPlayer=state::NO_PLAYER;
        this->authorPlayer=state::NO_PLAYER;
        this->commandTypeId =CommandTypeId::NO_COMMAND;
    };

    // Destructor
    Command::~Command() = default;

    // Getter for CommandTypeId
    CommandTypeId Command::getCommandTypeId() {
        return commandTypeId;
    }

    // Execute method
    void Command::execute(state::GameState &state) {}

    bool Command::check(state::GameState &state) {
        return authorPlayer==state.getPlaying();
    }


} // namespace engine
