#include "UseCharacterAbilityCommand.h"

namespace engine {

    UseCharacterAbilityCommand::UseCharacterAbilityCommand(state::PlayerId authorPlayer, state::PlayerId targetPlayer, state::CharacterType targetCharacter = state::CharacterType::NoCharacter){
        this->authorPlayer = authorPlayer;
        this->targetPlayer = authorPlayer;
        this->targetCharacter = targetCharacter;
    }

    UseCharacterAbilityCommand::~UseCharacterAbilityCommand() {
    }

    void UseCharacterAbilityCommand::execute(state::GameState& state) {
        // Getting the player to execute the command on
        state::Player player = state.getPlayer(authorPlayer);
        state::CharacterType character = player.getCharacter();

        // Applying the character ability 
        if (character == state::CharacterType::Assassin)
        {

        }
        else if (character == state::CharacterType::Thief)
        {
            
        }
        else if (character == state::CharacterType::Magician)
        {
            
        }
        else if (character == state::CharacterType::King)
        {
            
        }
        else if (character == state::CharacterType::Bishop)
        {
            
        }
        else if (character == state::CharacterType::Merchant)
        {
            
        }
        else if (character == state::CharacterType::Architect)
        {
            
        }
        else if (character == state::CharacterType::Warlord)
        {
            
        }

        // Updating
        state.updatePlayer(player);
    }

    void UseCharacterAbilityCommand::serialize() {
    }

} // namespace engine
