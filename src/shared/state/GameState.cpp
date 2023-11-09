#include "GameState.h"

class GameState{

};

namespace state {

    std::vector<Player> GameState::getListOfPlayer (){
        return this->listOfPlayers;
    }

    int GameState::getNbCardToDraw (){
        return this->nbOfCardToDraw;
    }

    Player* GameState::getCrownOwner (){
        return this->CrownOwner;
    }

    void GameState::setNbCardToDraw (int nbCard){
        this->nbOfCardToDraw = nbCard;
    }

    void GameState::setCrownOwner (Player* player){
        this->CrownOwner = player;
    }
}