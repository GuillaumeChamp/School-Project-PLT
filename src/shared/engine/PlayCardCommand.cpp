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
        state::Player player = state.getPlayer(authorPlayer);
        std::vector<state::Card> hand = player.getHand();

        hand.insert(hand.end(), card);

        player.setHand(hand);
        state.updatePlayer(player);
        

    }

    // Check method
    bool PlayCardCommand::check(state::GameState& state) {
        return true;
    }

} // namespace engine
