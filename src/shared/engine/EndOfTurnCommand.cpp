// EndOfTurnCommand.cpp
#include "EndOfTurnCommand.h"

namespace engine {

    // Constructor
    EndOfTurnCommand::EndOfTurnCommand(state::PlayerId authorPlayer) {
    }

    // Destructor
    EndOfTurnCommand::~EndOfTurnCommand() {
    }

    // Execute method
    void EndOfTurnCommand::execute(state::GameState &state) {

    }

    // Serialize method
    void EndOfTurnCommand::serialize() {
    }

    bool EndOfTurnCommand::check(state::GameState &state) {
        Command::check(state);
    }


} // namespace engine
