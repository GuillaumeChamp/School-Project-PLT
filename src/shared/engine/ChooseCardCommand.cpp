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
        // Getting the drawable cards
        std::vector<state::Card> drawableCards = state.getDrawableCards();

        if (drawableCards.empty())
        { // If there's no cards to draw, this means the expected action is to build a card
            auto* command = new BuildCommand(authorPlayer, &card);
            Engine::getInstance(state)->addCommand(command);
        }
        else // If there are cards to draw, this means the expected action is to add a card to the player's hand
        {
            state::Player player = state.getPlayer(authorPlayer);
            std::vector<state::Card> hand = player.getHand();

            hand.insert(hand.end(), card);
            drawableCards.erase(drawableCards.begin(), drawableCards.end());
        }
    }

    // Check method
    bool ChooseCardCommand::check(state::GameState& state) {
        return true;
    }

} // namespace engine
