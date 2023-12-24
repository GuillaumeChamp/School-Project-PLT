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
    BuildCommand::~BuildCommand() = default; //no need to delete card (cause double free)

    // Execute method
    void BuildCommand::execute(state::GameState &state) {
        // Getting the player to execute the command on
        state::Player player = state.getPlayer(authorPlayer);

        // Remove the card
        std::vector<state::Card> hand = player.getHand();
        hand.erase(std::remove_if(hand.begin(), hand.end(), [this](const state::Card &o) {
                       return o.getNameOfCard() == this->card->getNameOfCard();
                   }),
                   hand.end());
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
        state::Player player = state.getPlayer(authorPlayer);

        // find the card in player hand
        std::vector<state::Card> hand = player.getHand();
        auto indexOfCard = std::find_if(hand.begin(), hand.end(), [this](const state::Card &c) {
            return c.getNameOfCard() == this->card->getNameOfCard();
        });

        //  find the card in player board (using name)
        std::vector<state::Card> board = player.getBoardOfPlayer();
        auto indexOfCardInBoard = std::find_if(board.begin(), board.end(), [this](const state::Card &c) {
            return c.getNameOfCard() == this->card->getNameOfCard();
        });

        return Command::check(state)
               && indexOfCard != hand.end() //is player have the card in hand
               && indexOfCardInBoard == board.end() // is the player not already built this building
               && player.getNumberOfCoins() >= card->getCostOfCard(); //is the player can pay the card
    }

}
