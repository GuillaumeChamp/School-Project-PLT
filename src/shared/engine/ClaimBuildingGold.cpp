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
  void ClaimBuildingGold::execute(state::GameState state) {
    // Getting the player to execute the command on
    state::Player player = state.getPlayer(authorPlayer);

    // Getting his board, coins and character
    std::vector<state::Card> board = player.getBoardOfPlayer();
    int coins = player.getNumberOfCoins();
    state::CharacterType character = player.getCharacter();


    //Checking how many cards on his board match his character's color and adding coins accordingly
    if (character == state::CharacterType::King)
    {
      for (state::Card card : board){
        if (card.getColorOfCard() == state::CardType::Noble) {
          coins++;
        }
      }
    }
    else if (character == state::CharacterType::Bishop)
    {
      for (state::Card card : board){
        if (card.getColorOfCard() == state::CardType::Religious) {
          coins++;
        }
      }
    }
    else if (character == state::CharacterType::Merchant)
    {
      for (state::Card card : board){
        if (card.getColorOfCard() == state::CardType::Commercial) {
          coins++;
        }
      }
    }
    else if (character == state::CharacterType::Warlord)
    {
      for (state::Card card : board){
        if (card.getColorOfCard() == state::CardType::Military) {
          coins++;
        }
      }
    }

    // Setting the player's new number of coins
    player.setNumberOfCoins(coins);
    state.updatePlayer(player);
  }

  // Serialize method
  void ClaimBuildingGold::serialize() {
  }

} // namespace engine
