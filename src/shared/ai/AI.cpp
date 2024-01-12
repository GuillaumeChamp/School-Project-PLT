#include "AI.h"

namespace ai {
    
    AI::AI (state::GameState* state){
        this->state = state;
        listOfCommand = std::vector<std::unique_ptr<engine::Command>>();
        
    }

    AI::~AI()= default;

    void run (state::GameState* state, state::PlayerId playerId){
        
    }

}
