// EndOfTurnCommand.cpp
#include "EndOfTurnCommand.h"

using namespace engine;
using namespace state;

// Constructor
EndOfTurnCommand::EndOfTurnCommand(PlayerId authorPlayer) {
    this->authorPlayer = authorPlayer;
}

// Destructor
EndOfTurnCommand::~EndOfTurnCommand() = default;

// Execute method
void EndOfTurnCommand::execute(GameState &state) {

    Player player = state.getPlayer(authorPlayer);
    PlayerId currentPlayer = state.getPlaying();

    //In choose character phase the next player is resolved by player
    if (state.getGamePhase() == state::CHOOSE_CHARACTER) {
        auto lastPlayer = static_cast<PlayerId>((state.getCrownOwner() + 2) % 4 + 1);
        auto nextPlayer = static_cast<PlayerId>(currentPlayer % 4 + 1 );
        state.setPlaying(nextPlayer);
        //Change phase if current player is the last player
        if (currentPlayer == lastPlayer) {
            auto *command = new ChangePhaseCommand(authorPlayer, state.getGamePhase());
            if (command->check(state)){
                command->execute(state);
            }
            delete command;
        }
    }
    //In call character phase, the next player is resolved by character
    if (state.getGamePhase() == Phase::CALL_CHARACTER) {

        auto nextPlayer = NO_PLAYER;
        auto calledCharacterId = static_cast<CharacterType>(state.getCurrentCharacter() + 1);
        
        while (calledCharacterId < 9) {
            if (calledCharacterId != state.getKilledCharacter()) {
                if ((nextPlayer = state.getPlayerIdByCharacter(calledCharacterId)) != NO_PLAYER) {         
                    break;
                }
            }
            calledCharacterId = static_cast<CharacterType>(calledCharacterId + 1);
        }
        if (calledCharacterId == 9) {
            //All characters have been called, change phase
            auto *command = new ChangePhaseCommand(authorPlayer, state.getGamePhase());
            if (command->check(state)){
                command->execute(state);
            }
            delete command;
            state.setPlaying(state.getCrownOwner());
            return;
        }
        Player playerToInit = state.getPlayer(nextPlayer);
        // We check if player have been robbed before calling it
        if (calledCharacterId == state.getRobbedCharacter()) {
            auto coins = playerToInit.getNumberOfCoins();
            playerToInit.setNumberOfCoins(0);
            auto thief = state.getPlayer(state.getPlayerIdByCharacter(THIEF));
            thief.setNumberOfCoins(coins + thief.getNumberOfCoins());
            state.updatePlayer(thief);
        }
        //reset player options
        playerToInit.setDrawAvailability(true);
        playerToInit.setCapacityAvailability(true);
        state.updatePlayer(playerToInit);
        //Update state
        state.setPlaying(nextPlayer);
        state.setCurrentCharacter(calledCharacterId);
        auto* command = new ClaimBuildingGold(authorPlayer);
        if (command->check(state)){
            command->execute(state);
        }
        delete command;
    }
}

// Check method
bool EndOfTurnCommand::check(GameState &state) {
    return Command::check(state);
}
