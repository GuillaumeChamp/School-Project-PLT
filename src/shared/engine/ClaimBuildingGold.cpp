// ClaimBuildingGold.cpp
#include "ClaimBuildingGold.h"
#include "algorithm"
#include "set"

using namespace engine;

// Constructor
ClaimBuildingGold::ClaimBuildingGold(state::PlayerId authorPlayer) {
    this->authorPlayer = authorPlayer;
    this->targetPlayer = authorPlayer;
    this->commandTypeId = CommandTypeId::CLAIM_BUILDING_GOLD;
}

// Destructor
ClaimBuildingGold::~ClaimBuildingGold() = default;

// Execute method
void ClaimBuildingGold::execute(state::GameState &state) {
    // Getting the player to execute the command on
    state::Player player = state.getPlayer(authorPlayer);

    // Getting player board
    std::vector<state::Card> board = player.getBoardOfPlayer();

    state::CardType color;
    bool toCompute = false;
    // Resolve color to look for using character
    switch (player.getCharacter()) {
        case state::CharacterType::KING:
            toCompute = true;
            color = state::NOBLE;
            break;
        case state::CharacterType::BISHOP:
            toCompute = true;
            color = state::RELIGIOUS;
            break;
        case state::CharacterType::MERCHANT:
            toCompute = true;
            color = state::COMMERCIAL;
            break;
        case state::CharacterType::WARLORD:
            toCompute = true;
            color = state::MILITARY;
            break;
        default:
            break;
    }

    int goldEarned = toCompute ? (int) std::count_if(board.begin(), board.end(), [color](const state::Card &card) {
        return color == card.getColorOfCard();
    }) : 0;
    // Setting the player's new number of coins
    player.setNumberOfCoins(player.getNumberOfCoins() + goldEarned);
    state.updatePlayer(player);
}

// Check method
bool ClaimBuildingGold::check(state::GameState &state) {
    std::set<state::CharacterType> mySet{state::KING, state::BISHOP, state::MERCHANT, state::WARLORD};
    state::CharacterType character = state.getPlayer(authorPlayer).getCharacter();
    return Command::check(state) &&
           mySet.find(character) != mySet.end();
}
