// ClaimBuildingGold.cpp
#include "ClaimBuildingGold.h"


namespace engine {

  // Constructor
  ClaimBuildingGold::ClaimBuildingGold(state::PlayerId authorPlayer) {
    this->authorPlayer=authorPlayer;
  }

  // Destructor
  ClaimBuildingGold::~ClaimBuildingGold() {
  }

  // Execute method
  void ClaimBuildingGold::execute(state::GameState& state) {
    // Getting the player to execute the command on
    state::Player player = state.getPlayer(authorPlayer);

    // Getting his board, coins and character
    std::vector<state::Card> board = player.getBoardOfPlayer();
    int coins = player.getNumberOfCoins();
    state::CharacterType character = player.getCharacter();


    //Checking how many cards on his board match his character's color and adding coins accordingly
    if (character == state::CharacterType::KING)
    {
      for (state::Card card : board){
        if (card.getColorOfCard() == state::CardType::NOBLE) {
          coins++;
        }
      }
    }
    else if (character == state::CharacterType::BISHOP)
    {
      for (state::Card card : board){
        if (card.getColorOfCard() == state::CardType::RELIGIOUS) {
          coins++;
        }
      }
    }
    else if (character == state::CharacterType::MERCHANT)
    {
      for (state::Card card : board){
        if (card.getColorOfCard() == state::CardType::COMMERCIAL) {
          coins++;
        }
      }
    }
    else if (character == state::CharacterType::WARLORD)
    {
      for (state::Card card : board){
        if (card.getColorOfCard() == state::CardType::MILITARY) {
          coins++;
        }
      }
    }

    // Setting the player's new number of coins
    player.setNumberOfCoins(coins);
    state.updatePlayer(player);
  }

  // Check method
  bool check (state::GameState& state) {
    
  }

} // namespace engine