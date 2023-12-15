// EndOfTurnCommand.cpp
#include "EndOfTurnCommand.h"
#include <iostream>

namespace engine {

    // Constructor
    EndOfTurnCommand::EndOfTurnCommand(state::PlayerId authorPlayer) {
        this->authorPlayer = authorPlayer;
    }

    // Destructor
    EndOfTurnCommand::~EndOfTurnCommand() = default;

    // Execute method
    void EndOfTurnCommand::execute(state::GameState &state) {
        // Switch to the next player

        

        state::Player player = state.getPlayer(authorPlayer);
        
        bool win = player.getBoardOfPlayer().size() ==8;
        state::PlayerId currentPlayer = state.getPlaying();
        state::CharacterType currentCharacter = state.getCurrentCharacter();
        state::PlayerId lastPlayer = static_cast<state::PlayerId>((static_cast<int>(state.getCrownOwner()) + 2) % 4 + 1);
        
        if((state.getGamePhase()==state::Phase::CALL_CHARACTER)){

            //Change phase if curent player is lastplayer
            //curent player change 

            currentPlayer = static_cast<state::PlayerId>((static_cast<int>(currentPlayer) +1) %4 );
            currentCharacter = static_cast<state::CharacterType>((static_cast<int>(currentCharacter)%7) +1);
            state.setPlaying(currentPlayer);
            state.setCurrentCharacter(currentCharacter);
            
        
        }
        if((state.getGamePhase()==state::Phase::CALL_CHARACTER)&& win){

            //Change phase if authorPlayer is last player
            //curent player has win no need to change
            state.setGamePhase(state::Phase::END_GAME);
            std::cout<<"End of the Game"<<std::endl;
        
        }
        if(state.getGamePhase()==state::Phase::CHOOSE_CHARACTER){

            //Change phase if authorPlayer is last player
            //curent player change
            currentPlayer = static_cast<state::PlayerId>((static_cast<int>(currentPlayer) +1) %4 );
            state.setPlaying(currentPlayer);
        }


        // Check if we reached the last player and wrap around to the first player
        //if (currentPlayer > state::PLAYER_D) {
        //    currentPlayer = state::PLAYER_A;
        //}


    }

    // Serialize method
    void EndOfTurnCommand::serialize() {
        auto nextPlayer = static_cast<state::PlayerId>(static_cast<int>(authorPlayer) % 4 + 1);
        // Updating the state
        state.setPlaying(nextPlayer);

    }

    // Check method
    bool EndOfTurnCommand::check(state::GameState &state) {
        return Command::check(state);
    }


} // namespace engine
