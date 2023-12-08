// ChooseCharacterCommand.cpp
#include "ChooseCharacterCommand.h"

namespace engine {

    // Constructor
    ChooseCharacterCommand::ChooseCharacterCommand(state::PlayerId authorPlayer, state::CharacterType characterType)
            : Command() {
        this->authorPlayer = authorPlayer;
        this->character = characterType;
    }

    // Destructor
    ChooseCharacterCommand::~ChooseCharacterCommand() = default;

    // Execute method
    void ChooseCharacterCommand::execute(state::GameState &state) {
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

    bool ChooseCharacterCommand::check(state::GameState &state) {
        return Command::check(state);
    }


} // namespace engine
