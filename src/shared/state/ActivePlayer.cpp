//
// Created by guillaume on 10/21/23.
//
#include "ActivePlayer.h"

namespace state {

    std::vector<Card> ActivePlayer::getHand(){
        return this->PlayerHand;
    }

}