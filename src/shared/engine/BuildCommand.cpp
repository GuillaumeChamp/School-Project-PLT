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

        // Remove the card
        std::vector<state::Card> hand = player.getHand();
        for (auto i = hand.begin(); i < hand.end(); i++) {
            if (hand[i - hand.begin()].getNameOfCard() == card->getNameOfCard()) {
                hand.erase(i);
                break;
            }
        }
        player.setHand(hand);

        // Update coins
        int coins = player.getNumberOfCoins();
        coins = coins - card->getCostOfCard();
        player.setNumberOfCoins(coins);
        // Update board
        std::vector<state::Card> board = player.getBoardOfPlayer();
        board.push_back(*card);
        player.setBoardOfPlayer(board);
        // Push the update to the engine
        state.updatePlayer(player);
    }


    // Check method
    bool BuildCommand::check(state::GameState &state) {
        if (!Command::check(state)){
            return false;
        }
        state::Player player = state.getPlayer(authorPlayer);

        // Check if the player owns the card
        std::vector<state::Card> hand = player.getHand();
        bool found = false;
        for (auto i = hand.begin(); i < hand.end(); i++) {
            if (hand[i - hand.begin()].getNameOfCard() == card->getNameOfCard()) {
                found = true;
                break;
            }
        }
        if (!found) return false; // If the player doesn't own the card, return

        //  Check if the player hasn't already built the same card
        std::vector<state::Card> board = player.getBoardOfPlayer();
        for (const state::Card &c: board) {
            if (c.getNameOfCard() == card->getNameOfCard()) {
                return false; // If he did, return
            }
        }

        // Check if the player has enough coins
        if (player.getNumberOfCoins() < card->getCostOfCard()) {
            return false;
        }

        return true;
    }


}
