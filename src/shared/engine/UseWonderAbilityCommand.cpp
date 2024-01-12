#include "UseWonderAbilityCommand.h"

namespace engine {

    // Constructor
    UseWonderAbilityCommand::UseWonderAbilityCommand(state::PlayerId authorPlayer, state::PlayerId targetPlayer, const state::Card& card) : card(card) {
        this->authorPlayer = authorPlayer;
        this->targetPlayer = targetPlayer;
        this->card = card;
    }

    // Destructor
    UseWonderAbilityCommand::~UseWonderAbilityCommand() = default;

    // Execute method
    void UseWonderAbilityCommand::execute(state::GameState& state) {
        // Getting the players corresponding to the Ids
        state::Player player = state.getPlayer(authorPlayer);
        state::Player targeted = state.getPlayer(targetPlayer);

        // Applying the wonder ability 
        if (card.getNameOfCard() == "Laboratoire") 
        {
            // Une fois par tour, défausser une carte contre 1 pièce
            std::vector<state::Card> hand = player.getHand();
        }
        else if (card.getNameOfCard() == "Manufacture") 
        { // Once per turn, you can use 3 coins to draw 3 cards
            // Getting the player's hand and coins
            std::vector<state::Card> hand = player.getHand();
            int coins = player.getNumberOfCoins();

            // Creating a DrawCommand
            auto* command = new DrawCommand(authorPlayer);
            Engine::getInstance().addCommand(command);

            // Deducing the coins
            coins = coins - 3;
            player.setNumberOfCoins(coins);

            // Updating the state
            state.updatePlayer(player);
        }
    }

    // Check method
    bool UseWonderAbilityCommand::check(state::GameState& state) {
        return Command::check(state);
    }

} // namespace engine
