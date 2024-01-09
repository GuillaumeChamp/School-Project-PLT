#include "PlayCardCommand.h"

namespace engine {

    // Constructor
    PlayCardCommand::PlayCardCommand(state::PlayerId authorPlayer, const state::Card& card) : card(card){
        this->authorPlayer = authorPlayer;
        this->card = card;
        this->commandTypeId = CommandTypeId::CHOOSE_CARD;
    }

    // Destructor
    PlayCardCommand::~PlayCardCommand() = default;

    // Execute method
    void PlayCardCommand::execute(state::GameState& state) {
        // Getting the player to execute the command on and his hand
        state::Player player = state.getPlayer(authorPlayer);
        std::vector<state::Card> hand = player.getHand();

        // Adding the new card to the player's hand
        hand.insert(hand.end(), card);
        
        // Setting the player's new hand, his draw availability and updating the state
        player.setHand(hand);
        state.updatePlayer(player);
    }

    // Check method
    bool PlayCardCommand::check(state::GameState& state) {
        return true;
    }

} // namespace engine
