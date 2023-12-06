// ChooseCharacterCommand.cpp
#include "ChooseCharacterCommand.h"
#include <iostream>

namespace engine {

  // Constructor
  ChooseCharacterCommand::ChooseCharacterCommand(state::PlayerId authorPlayer, state::CharacterType characterType): Command(){
    this->authorPlayer=authorPlayer;
    this->character=characterType;
  }

  // Destructor
  ChooseCharacterCommand::~ChooseCharacterCommand() {
  }

  // Execute method
  void ChooseCharacterCommand::execute(state::GameState state) {
    // Getting the player to execute the command on
    state::Player player = state.getPlayer(authorPlayer);

    // Setting the player's character
    player.setCharacter(character);

    // Updating
    state.updatePlayer(player);
  }

  // Serialize method
  void ChooseCharacterCommand::serialize() {
  }


} // namespace engine
