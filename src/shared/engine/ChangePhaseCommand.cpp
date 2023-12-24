// ChangePhaseCommand.cpp
#include "ChangePhaseCommand.h"

namespace engine {

    // Constructor
    ChangePhaseCommand::ChangePhaseCommand(state::PlayerId authorPlayer, state::Phase phase) {
        this->authorPlayer = authorPlayer;
        this->phase = phase;
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
                if (!isPlayerWin) {
                    this->phase = state::Phase::CHOOSE_CHARACTER;
                    //reset character list
                    state.setAvailableCharacter({state::CharacterType::ASSASSIN,
                                                 state::CharacterType::THIEF,
                                                 state::CharacterType::MAGICIAN,
                                                 state::CharacterType::KING,
                                                 state::CharacterType::BISHOP,
                                                 state::CharacterType::MERCHANT,
                                                 state::CharacterType::ARCHITECT,
                                                 state::CharacterType::WARLORD});
                } else {
                    this->phase = state::Phase::END_GAME;
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

}
