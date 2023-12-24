// Command.cpp
#include "Command.h"

namespace engine {

    // Constructor
    Command::Command(){
        this->targetPlayer=state::NO_PLAYER;
        this->authorPlayer=state::NO_PLAYER;
        this->commandTypeId =CommandTypeId::SWITCH_PHASE; //bancale
    };

    // Destructor
    Command::~Command() = default;

    // Getter for CommandTypeId
    CommandTypeId Command::getCommandTypeId() {
        return commandTypeId;
    }

    // Execute method
    void Command::execute(state::GameState &state) {

        // Implement the logic to execute the command on the game state
        // You may use the 'playing' and 'card' attributes in this method
    }

    bool Command::check(state::GameState &state) {
        return authorPlayer==state.getPlaying();
    }


} // namespace engine
