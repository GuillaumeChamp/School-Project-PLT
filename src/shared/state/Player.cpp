//
// Created by guillaume on 10/22/23.
//

#include "Player.h"

class Player{

};

namespace state {

std::string Player::getNameOfPlayer() {
    return this->nameOfPlayer;
}

std::vector<Card> Player::getBoardOfPlayer() {
    return this->board;
}

int Player::getNumberOfCoins() {
    return this->numberOfCoins;
}

int Player::getNumberOfCards() {
    return this->numberOfCards;
}

void Player::setBoardOfPlayer(const std::vector<Card> board) {
    this->board = board;
}

void Player::setNumberOfCards (int nbOfCards) {
    this->numberOfCards = nbOfCards;
}

void Player::setNumberOfCoins (int nbOfCoins) {
    this->numberOfCoins = nbOfCoins;
}

}