//
// Created by guillaume on 10/21/23.
//
#include "ActivePlayer.h"

class ActivePlayer{

};

namespace state {

    std::vector<Card> ActivePlayer::getHand(){
        return this->playerHand;
    }

    void ActivePlayer::setHand (std::vector<Card> hand){
        this->playerHand = hand;
    }

}