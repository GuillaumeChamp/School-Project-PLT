// ChangePhaseCommand.cpp
#include "ChangePhaseCommand.h"

namespace engine {

    // Constructor
    ChangePhaseCommand::ChangePhaseCommand(state::PlayerId authorPlayer, state::Phase phase) {
      this->authorPlayer=authorPlayer;
      this->phase=phase;
      

    }

    // Destructor
    ChangePhaseCommand::~ChangePhaseCommand() {
    }

    // Execute method
    void ChangePhaseCommand::execute(state::GameState &state) {
      state::Player currentPlayer = state.getPlayer(authorPlayer);
      bool win = currentPlayer.getBoardOfPlayer().size() ==8;
    
       switch (this->phase) { 
          case state::Phase::START_GAME :
                this->phase = state::Phase::CHOOSE_CHARACTER;
                break;
          case state::Phase::CHOOSE_CHARACTER :
                this->phase = state::Phase::CALL_CHARACTER;
                break;
          case state::Phase::END_GAME:
                break;
          case state::Phase::CALL_CHARACTER :
                  if(win){
                  this->phase = state::Phase::END_GAME;
                  }
                  else{
                  this->phase = state::Phase::CHOOSE_CHARACTER;
                  }
                
                break;
        }
        
        state.setGamePhase(this->phase);
      
    }

    // Check method
    bool ChangePhaseCommand::check(state::GameState &state) {
        return Command::check(state);
    }


} // namespace engine
