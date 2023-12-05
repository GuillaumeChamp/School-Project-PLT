// ChooseCharacterCommand.cpp
#include "ChooseCharacterCommand.h"
#include <iostream>

namespace engine {

  // Constructor
  ChooseCharacterCommand::ChooseCharacterCommand(state::PlayerId authorPlayer, state::CharacterType characterType): Command(){

  }


  // Destructor
  ChooseCharacterCommand::~ChooseCharacterCommand() {
  }

  // Execute method
  void ChooseCharacterCommand::execute(state::GameState state) {
    /*switch (playing) {

        case state::Playing::PLAYERA:
            std::cout <<"A is a "<< characterType << std::endl;
            break;

        case state::Playing::PLAYERB:
            std::cout <<"B is a "<< characterType <<std::endl;
            break;
          
          case state::Playing::PLAYERC:
            std::cout <<"C is a "<< characterType <<std::endl;
            break;
          
          case state::Playing::PLAYERD:
            std::cout <<"D is a "<< characterType <<std::endl;
            break;

        default:
            
            break;
    }*/

  }

  // Serialize method
  void ChooseCharacterCommand::serialize() {
  }


} // namespace engine
