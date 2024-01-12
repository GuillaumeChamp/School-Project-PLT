#include "GetCardCommand.h"

namespace engine {

    // Constructor
    GetCardCommand::GetCardCommand(state::PlayerId authorPlayer, const state::Card& card) : card(card){
        this->authorPlayer = authorPlayer;
        this->card = card;
        this->commandTypeId = CommandTypeId::CHOOSE_CARD;
    }

    // Destructor
    GetCardCommand::~GetCardCommand() = default;

    // Execute method
    void GetCardCommand::execute(state::GameState& state) {
        // Getting the player to execute the command on and his hand
        state::Player player = state.getPlayer(authorPlayer);
        std::vector<state::Card> hand = player.getHand();
        // Adding the new card to the player's hand
        hand.insert(hand.end(), card);
        
        // Setting the player's new hand and updating the state
        player.setHand(hand);
        state.updatePlayer(player);
    }

    // Check method
    bool GetCardCommand::check(state::GameState& state) {
        bool isInDrawableCards = false;
        for (state::Card card1 : state.getDrawableCards()){
            if (card1.getNameOfCard() == card.getNameOfCard()){
                isInDrawableCards = true;
            }
        }
        return true && isInDrawableCards;
    }

} // namespace engine
