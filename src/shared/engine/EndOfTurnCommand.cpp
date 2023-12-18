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
        
        
        state::PlayerId currentPlayer = state.getPlaying();
        state::CharacterType currentCharacter = state.getCurrentCharacter();
        state::PlayerId lastPlayer = static_cast<state::PlayerId>((static_cast<int>(state.getCrownOwner()) + 2) % 4 + 1);
        
        if((state.getGamePhase()==state::Phase::CALL_CHARACTER)){

            //Change phase if curent player is lastplayer
            //curent player change 

            currentPlayer = static_cast<state::PlayerId>((static_cast<int>(currentPlayer)%4)+1 );
            currentCharacter = static_cast<state::CharacterType>((static_cast<int>(currentCharacter)%7) +1);
            state.setPlaying(currentPlayer);
            state.setCurrentCharacter(currentCharacter);
            
        
        }
        if(state.getGamePhase()==state::Phase::CHOOSE_CHARACTER){

            //Change phase if authorPlayer is last player
            //curent player change
            currentPlayer = static_cast<state::PlayerId>((static_cast<int>(currentPlayer)%4) + 1 );
            state.setPlaying(currentPlayer);
        }


        


    }





    // Check method
    bool EndOfTurnCommand::check(state::GameState &state) {
        return Command::check(state);
    }


} // namespace engine
