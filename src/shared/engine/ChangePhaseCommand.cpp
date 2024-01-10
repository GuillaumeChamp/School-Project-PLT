// ChangePhaseCommand.cpp
#include "ChangePhaseCommand.h"

using namespace engine;

// Constructor
ChangePhaseCommand::ChangePhaseCommand(state::PlayerId authorPlayer, state::Phase phase) {
    this->authorPlayer = authorPlayer;
    this->phase = phase;
    this->commandTypeId = CommandTypeId::SWITCH_PHASE;
}

// Destructor
ChangePhaseCommand::~ChangePhaseCommand() = default;

// Execute method
void ChangePhaseCommand::execute(state::GameState &state) {
    state::Player currentPlayer = state.getPlayer(authorPlayer);
    bool isPlayerWin = currentPlayer.getBoardOfPlayer().size() == 8;

    switch (this->phase) {
        case state::Phase::START_GAME :
        case state::Phase::CALL_CHARACTER :
            if (isPlayerWin) {
                this->phase = state::Phase::END_GAME;
            } else {
                this->phase = state::Phase::CHOOSE_CHARACTER;
                state.setKilledCharacter(state::NO_CHARACTER);
                state.setRobbedCharacter(state::NO_CHARACTER);
                state.setPlaying(state.getCrownOwner());
                state.setCurrentCharacter(state::NO_CHARACTER);
                //reset character list
                state.setAvailableCharacter({state::CharacterType::ASSASSIN,
                                             state::CharacterType::THIEF,
                                             state::CharacterType::MAGICIAN,
                                             state::CharacterType::KING,
                                             state::CharacterType::BISHOP,
                                             state::CharacterType::MERCHANT,
                                             state::CharacterType::ARCHITECT,
                                             state::CharacterType::WARLORD});
            }
            break;
        case state::Phase::CHOOSE_CHARACTER :
            this->phase = state::Phase::CALL_CHARACTER;
            break;
        case state::Phase::END_GAME:
            break;
    }
    state.setGamePhase(this->phase);
}

// Check method
bool ChangePhaseCommand::check(state::GameState &state) {
    return Command::check(state);
}
