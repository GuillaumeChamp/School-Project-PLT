// Gain2GoldCommand.cpp
#include "GainGoldCommand.h"
#include <iostream>


namespace engine {

    // Constructor
    GainGoldCommand::GainGoldCommand(state::PlayerId authorPlayer, int nbOfGolds) : Command() {
      
      this->nbOfGold=nbOfGolds;
    
      this->authorPlayer=authorPlayer;

    }

    // Destructor
    GainGoldCommand::~GainGoldCommand() {
    }

    // Execute method
    void GainGoldCommand::execute(state::GameState &state) {

      state::Player player = state.getPlayer(this->authorPlayer);

      player.setNumberOfCoins(player.getNumberOfCoins()+nbOfGold);

    }


    // Serialize method
    void GainGoldCommand::serialize() {
    }


    // Check method
    bool GainGoldCommand::check(state::GameState &state) {
          return Command::check(state);
    }


} // namespace engine
