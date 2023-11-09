//
// Created by guillaume on 10/22/23.
//

#include "Player.h"

class Player{

};

namespace state {

Player::Player(std::string name, state::PlayerId id){
    this->nameOfPlayer = name;
    this->playerId = id;
}

Player::~Player(){
    //delete &nameOfPlayer;
}

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