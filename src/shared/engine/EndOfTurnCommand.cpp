// EndOfTurnCommand.cpp
#include "EndOfTurnCommand.h"

namespace engine {

    // Constructor
    EndOfTurnCommand::EndOfTurnCommand(state::PlayerId authorPlayer) {
        this->authorPlayer = authorPlayer;
    }

    // Destructor
    EndOfTurnCommand::~EndOfTurnCommand() = default;

    // Execute method
    void EndOfTurnCommand::execute(state::GameState &state) {
        // Switch to the next player
        auto nextPlayer = static_cast<state::PlayerId>(static_cast<int>(authorPlayer) % 4 + 1);
        // Updating the state
        state.setPlaying(nextPlayer);
    }

    // Serialize method
    void EndOfTurnCommand::serialize() {
    }

    bool EndOfTurnCommand::check(state::GameState &state) {
        return Command::check(state);
    }


} // namespace engine
