// ChooseCharacterCommand.cpp
#include "ChooseCharacterCommand.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <iostream>

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

        //on récupère les characters disponible pour pouvoir valider la commande
        state::Player player = state.getPlayer(this->authorPlayer);
        std::vector<state::CharacterType> availableCharacters = state.getAvailableCharacter();

        //on efface de la liste des characters dispo le character selectionné par le joueur
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
        state::Player player = state.getPlayer(this->authorPlayer);
        bool characterIsAvaible;
        bool noCharacter = state::CharacterType::NO_CHARACTER==player.getCharacter();
        std::vector<state::CharacterType> availableCharacters = state.getAvailableCharacter();
        auto it = std::find(availableCharacters.begin(), availableCharacters.end(), this->character);

        if (it != availableCharacters.end()) { characterIsAvaible=true;} 
        else {characterIsAvaible=false;}
        return (Command::check(state) && characterIsAvaible && noCharacter);
    }


} // namespace engine
