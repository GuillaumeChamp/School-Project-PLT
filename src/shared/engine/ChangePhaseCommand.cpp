// ChangePhaseCommand.cpp
#include "ChangePhaseCommand.h"

namespace engine {

  // Constructor
  ChangePhaseCommand::ChangePhaseCommand(state::PlayerId authorPlayer) {
    this->authorPlayer=authorPlayer;

  }

  // Destructor
  ChangePhaseCommand::~ChangePhaseCommand() {
  }

  // Execute method
  void ChangePhaseCommand::execute(state::GameState& state) {
    state.nextGamePhase();
  }


} // namespace engine
