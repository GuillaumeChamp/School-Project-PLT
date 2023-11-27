// DrawCommand.cpp
#include "DrawCommand.h"

namespace engine {

  // Constructor
  DrawCommand::DrawCommand(state::PlayerId authorPlayer, int nbOfCards) : nbOfCards(nbOfCards) {
  }

  // Destructor
  DrawCommand::~DrawCommand() {
  }

  // Execute method
  void DrawCommand::execute(state::GameState state) {

  }

  // Serialize method
  void DrawCommand::serialize() {
  }


} // namespace engine
