#include "PlayCardCommand.h"

namespace engine {

    // Constructor
    PlayCardCommand::PlayCardCommand(state::PlayerId authorPlayer, state::Card card) : card(card) {
        this->authorPlayer = authorPlayer;
        this->card = card;
    }

    // Destructor
    PlayCardCommand::~PlayCardCommand() {
    }

    // Execute method
    void PlayCardCommand::execute(state::GameState& state) {
        // 
        auto* command = new ChooseCardCommand(authorPlayer, card);
        Engine::getInstance(state)->addCommand(command);
    }

    // Check method
    bool PlayCardCommand::check(state::GameState& state) {
        return true;
    }

} // namespace engine
