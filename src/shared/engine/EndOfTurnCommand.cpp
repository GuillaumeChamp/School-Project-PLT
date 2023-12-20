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
        
            state::Player playerToInit = state.getPlayer(currentPlayer);
            //reinitialise les capacité activables une fois par tour
            playerToInit.setDrawAvailability(true);
            playerToInit.setCapacityAvailability(true);
            state.updatePlayer(playerToInit);
            //rotation du current character
            currentCharacter = static_cast<state::CharacterType>((static_cast<int>(currentCharacter)%7) +1);
            //check si on PEUT appeler le character

            if(currentCharacter==state.getKilledCharacter()){
            currentCharacter = static_cast<state::CharacterType>((static_cast<int>(currentCharacter)%7) +1);
            }

            //si l'auteur de la commande de fin de tour est le dernier joueur on change de phase
            if(authorPlayer==lastPlayer){
            //appel de commande de changement de phase 
            auto* command = new ChangePhaseCommand(authorPlayer, state.getGamePhase());
            Engine::getInstance(state)->addCommand(command);
            }
        //MAJ du state 
            state.setPlaying(currentPlayer);
            state.setCurrentCharacter(currentCharacter);

        }
        if(state.getGamePhase()==state::Phase::CHOOSE_CHARACTER){

            //Change phase if authorPlayer is last player
            //curent player change
            currentPlayer = static_cast<state::PlayerId>((static_cast<int>(currentPlayer)%4) + 1 );
            state::Player playerToInit = state.getPlayer(currentPlayer);

            //si l'auteur de la commande de fin de tour est le dernier joueur on change de phase
            if(authorPlayer==lastPlayer){
            //appel de commande de changement de phase 
            auto* command = new ChangePhaseCommand(authorPlayer, state.getGamePhase());
            Engine::getInstance(state)->addCommand(command);
            }
            //reinitialise les capacité activables une fois par tour
            playerToInit.setDrawAvailability(true);
            playerToInit.setCapacityAvailability(true);
            state.setPlaying(currentPlayer);

        }
    }

    // Check method
    bool EndOfTurnCommand::check(state::GameState &state) {
        return Command::check(state);
    }


} // namespace engine
