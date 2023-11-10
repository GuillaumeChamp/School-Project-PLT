//
// Created by guillaume on 10/22/23.
//

#include "Player.h"

namespace state {

Player::Player(std::string name, state::PlayerId id){
    this->nameOfPlayer = name;
    this->playerId = id;
    this->numberOfCoins = 2;
    this->character = CharacterType::NoCharacter;
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
    return this->hand.size();
}

void Player::setBoardOfPlayer(const std::vector<Card> board) {
    this->board = board;
}


void Player::setNumberOfCoins (int nbOfCoins) {
    this->numberOfCoins = nbOfCoins;
}

    PlayerId Player::getIdOfPlayer() {
        return this->playerId;
    }

    CharacterType Player::getCharacter() {
        return this->character;
    }

    void Player::setCharacter(CharacterType character) {
        this->character=character;
    }

    void Player::setHand(std::vector<Card> hand) {
        this->hand=hand;
    }

    std::vector<Card> Player::getHand() {
        return this->hand;
    }

}