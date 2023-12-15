// ChooseCharacterCommand.cpp
#include "ChooseCharacterCommand.h"
#include <vector>
#include <iostream>
#include <algorithm>

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
        state::Player player = state.getPlayer(this->authorPlayer);
        std::vector<state::CharacterType> availableCharacters = state.getAvailableCharacter();
        availableCharacters.erase(
            std::remove(availableCharacters.begin(), availableCharacters.end(), this->character),
            availableCharacters.end()
        );
        
        state.setAvailableCharacter(availableCharacters);
        player.setCharacter(this->character);
        state.updatePlayer(player);
        

    }

    // Check method
    bool ChooseCharacterCommand::check(state::GameState &state) {
        return Command::check(state);
    }


} // namespace engine
