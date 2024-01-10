#include "RandomAI.h"

namespace ai{

    RandomAI::RandomAI(state::GameState* state, int randomSeed):AI(state::GameState* state) {
        this->state=state;
        this->randgen=randgen(randomSeed); 
    }

    RandomAI::~RandomAI() = {
        this->listOfCommand.clear();
    };

    void run (state::GameState* state, state::PlayerId playerId){

        isPlaying=state->getPlaying()==playerId;
        
        if (state->getPhase() == && isPlaying){

        }

        command = new 
        // Retourne l'élément choisi aléatoirement
        std::uniform_int_distribution<std::size_t> distribution(0, listOfCommand.size() - 1);
        std::size_t randomIndex = distribution(randgen);

        command = listOfCommand[randomIndex];

    }

}