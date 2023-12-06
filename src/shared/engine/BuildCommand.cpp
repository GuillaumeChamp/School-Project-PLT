// BuildCommand.cpp
#include "BuildCommand.h"
#include <algorithm>

namespace engine {

    // Constructor
    BuildCommand::BuildCommand(state::PlayerId authorPlayer, state::Card *card) : engine::Command() {
        this->authorPlayer = authorPlayer;
        this->targetPlayer = authorPlayer;
        this->card = card;
    }

    // Destructor
    BuildCommand::~BuildCommand() = default;

    // Execute method
    void BuildCommand::execute(state::GameState &state) {
        // Getting the player to execute the command on
        state::Player player = state.getPlayer(authorPlayer);

        // Check if card is present
        std::vector<state::Card> hand = player.getHand();
        for (auto i = hand.begin(); i < hand.end(); i++) {
            if (hand[i - hand.begin()].getNameOfCard() == card->getNameOfCard()) {
                hand.erase(i);

                // Checking if he has enough coins to build the card
                if (player.getNumberOfCoins() < card->getCostOfCard()) {
                    return;
                }

                // Getting his board, hand and coins
                std::vector<state::Card> board = player.getBoardOfPlayer();
                int coins = player.getNumberOfCoins();

                // Checking if the player has already built an identical card
                for (const state::Card &c: board) {
                    if (c.getNameOfCard() == card->getNameOfCard()) {
                        return;
                    }
                }

                // Modifying the player's attributes
                board.push_back(*card);
                coins = coins - card->getCostOfCard();

                // Setting the player's new board, hand and coins
                player.setBoardOfPlayer(board);
                player.setHand(hand);
                player.setNumberOfCoins(coins);
                state.updatePlayer(player);
                
                break;
            }
        }
    }


    // Serialize method
    void BuildCommand::serialize() {

    }


} // namespace engine
