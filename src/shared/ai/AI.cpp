#include "AI.h"

namespace ai {
    
    AI::AI (std::shared_ptr<state::GameState> state,state::PlayerId playerId){
        this->state = std::move(state);
        this->playerId = playerId;
    }

    void AI::run() {

    }

    AI::~AI()= default;

}
