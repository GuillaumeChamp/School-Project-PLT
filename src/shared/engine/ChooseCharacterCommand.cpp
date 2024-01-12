// ChooseCharacterCommand.cpp
#include "ChooseCharacterCommand.h"
#include "EndOfTurnCommand.h"
#include "algorithm"

using namespace engine;

// Constructor
ChooseCharacterCommand::ChooseCharacterCommand(state::PlayerId authorPlayer, state::CharacterType characterType)
        : Command() {
    this->authorPlayer = authorPlayer;
    this->character = characterType;
    this->commandTypeId = CommandTypeId::CHOOSE_CHARACTER;
}

// Destructor
ChooseCharacterCommand::~ChooseCharacterCommand() = default;

// Execute method
void ChooseCharacterCommand::execute(state::GameState &state) {
    //recover player and list of remaining character
    state::Player player = state.getPlayer(this->authorPlayer);
    std::vector<state::CharacterType> availableCharacters = state.getAvailableCharacter();

    player.setCharacter(this->character);
    //Remove the selected character
    availableCharacters.erase(
            std::remove(availableCharacters.begin(), availableCharacters.end(), this->character),
            availableCharacters.end()
    );

    //update the state
    state.setAvailableCharacter(availableCharacters);
    state.updatePlayer(player);
    auto *command = new EndOfTurnCommand(authorPlayer);
    if (command->check(state)){
        command->execute(state);
    }
    delete command;
}

// Check method
bool ChooseCharacterCommand::check(state::GameState &state) {
    state::Player player = state.getPlayer(this->authorPlayer);
    std::vector<state::CharacterType> availableCharacters = state.getAvailableCharacter();

    auto indexOfCharacter = std::find(availableCharacters.begin(), availableCharacters.end(), this->character);
    return Command::check(state)
           && state::CharacterType::NO_CHARACTER == player.getCharacter() //NO_CHARACTER cannot be picked
           && indexOfCharacter !=
              availableCharacters.end(); //targeted character must be found is the list of available characters
}
