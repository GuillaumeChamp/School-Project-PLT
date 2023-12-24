#include "ChooseCardCommand.h"

namespace engine {

    // Constructor
    ChooseCardCommand::ChooseCardCommand(state::PlayerId authorPlayer, const state::Card &card) : card(card) {
        this->authorPlayer = authorPlayer;
        this->card = card;
    }

    // Destructor
    ChooseCardCommand::~ChooseCardCommand() = default;

    // Execute method
    void ChooseCardCommand::execute(state::GameState &state) {

    }

    // Check method
    bool ChooseCardCommand::check(state::GameState &state) {
        return Command::check(state);
    }

}
