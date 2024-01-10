#include "AI.h"

namespace ai {
    
    AI::AI (state::GameState* state){
        this->state = state;
        this->listOfCommand = new std::vector<engine::Command> ;
    }

    AI::~AI()= default;

    void run (state::GameState* state, state::PlayerId playerId){
        
    }

}
