// BuildCommand.cpp
#include "BuildCommand.h"
#include <algorithm>

using namespace engine;

// Constructor
BuildCommand::BuildCommand(state::PlayerId authorPlayer, const state::Card& card)  : card(card) {
    this->authorPlayer = authorPlayer;
    this->targetPlayer = authorPlayer;
    this->commandTypeId = CommandTypeId::BUILD;
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
                   return o.getNameOfCard() == this->card.getNameOfCard();
               }),
               hand.end());
    player.setHand(hand);

    // Update coins
    int coins = player.getNumberOfCoins();
    coins = coins - card.getCostOfCard();
    player.setNumberOfCoins(coins);
    // Update board
    std::vector<state::Card> board = player.getBoardOfPlayer();
    board.push_back(card);
    player.setBoardOfPlayer(board);
    // Push the update to the engine
    state.updatePlayer(player);
}


// Check method
bool BuildCommand::check(state::GameState &state) {
    state::Player player = state.getPlayer(authorPlayer);

    // check if the player has the card in his hand
    std::vector<state::Card> hand = player.getHand();
    auto indexOfCard = std::find_if(hand.begin(), hand.end(), [this](const state::Card &c) {
        return c.getNameOfCard() == this->card.getNameOfCard();
    });

    // check if the player has already built this card (using name)
    std::vector<state::Card> board = player.getBoardOfPlayer();
    auto indexOfCardInBoard = std::find_if(board.begin(), board.end(), [this](const state::Card &c) {
        return c.getNameOfCard() == this->card.getNameOfCard();
    });

    return Command::check(state)
           && indexOfCard != hand.end() // does the player have the card in hand
           && indexOfCardInBoard == board.end() // did the player not already build this building
           && player.getNumberOfCoins() >= card.getCostOfCard(); // can the player pay the card
}
