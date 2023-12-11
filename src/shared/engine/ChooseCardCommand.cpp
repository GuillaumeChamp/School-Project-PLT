#include "ChooseCardCommand.h"

namespace engine {

    // Constructor
    ChooseCardCommand::ChooseCardCommand(state::PlayerId authorPlayer, state::Card card) : card(card) {
        this->authorPlayer = authorPlayer;
        this->card = card;
    }

    // Destructor
    ChooseCardCommand::~ChooseCardCommand() {
    }

    // Execute method
    void ChooseCardCommand::execute(state::GameState& state) {

    }

    // Serialization method
    void ChooseCardCommand::serialize() {
    }

    // Check method
    bool ChooseCardCommand::check(state::GameState& state) {
        return true;
    }

} // namespace engine
