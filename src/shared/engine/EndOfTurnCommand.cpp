// EndOfTurnCommand.cpp
#include "EndOfTurnCommand.h"

namespace engine {

    // Constructor
    EndOfTurnCommand::EndOfTurnCommand(state::PlayerId authorPlayer) {
        this->authorPlayer = authorPlayer;
    }

    // Destructor
    EndOfTurnCommand::~EndOfTurnCommand() {
    }

    // Execute method
    void EndOfTurnCommand::execute(state::GameState &state) {
        // Switch to the next player
        state::PlayerId currentPlayer = static_cast<state::PlayerId>(static_cast<int>(authorPlayer) + 1);

        // Check if we reached the last player and wrap around to the first player
        if (currentPlayer > state::PlayerD) {
            currentPlayer = state::PlayerA;
        }

        // Updating the state
        state.setPlaying(currentPlayer);
    }

    // Serialize method
    void EndOfTurnCommand::serialize() {
    }

    bool EndOfTurnCommand::check(state::GameState &state) {
        return Command::check(state);
    }


} // namespace engine
