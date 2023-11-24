// Gain2GoldCommand.cpp
#include "Gain2GoldCommand.h"

namespace engine {

  // Constructor
  Gain2GoldCommand::Gain2GoldCommand(state::Playing playing, int nbOfGolds) : nbofGolds(nbOfGolds) {
  }

  // Destructor
  Gain2GoldCommand::~Gain2GoldCommand() {
  }

  // Execute method
  void Gain2GoldCommand::execute(state::GameState state) {
    // state.gainGold(playing, nbofGolds);
  }

  // Serialize method
  void Gain2GoldCommand::serialize() {

  }


} // namespace engine
