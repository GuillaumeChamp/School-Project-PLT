//
// Created by guillaume on 10/22/23.
//

#include "Player.h"

#include <utility>

namespace state {

Player::Player(std::string name, state::PlayerId id){
    this->nameOfPlayer = std::move(name);
    this->playerId = id;
    this->numberOfCoins = 2;
    this->character = CharacterType::NoCharacter;
    this->isCapacityAvailable= false;
}

Player::~Player() {
    this->hand.clear();
    this->board.clear();
}

std::string Player::getNameOfPlayer() const{
    return this->nameOfPlayer;
}

std::vector<Card> Player::getBoardOfPlayer() const{
    return this->board;
}

int Player::getNumberOfCoins() const{
    return this->numberOfCoins;
}

int Player::getNumberOfCards() const{
    return (int) this->hand.size();
}

void Player::setBoardOfPlayer(std::vector<Card> board) {
    this->board.clear();
    this->board = std::move(board);
}


void Player::setNumberOfCoins (int nbOfCoins) {
    this->numberOfCoins = nbOfCoins;
}

    PlayerId Player::getIdOfPlayer() const{
        return this->playerId;
    }

    CharacterType Player::getCharacter() const{
        return this->character;
    }

    void Player::setCharacter(CharacterType character) {
        this->character=character;
    }

    void Player::setHand(std::vector<Card> hand) {
        this->hand.clear();
        this->hand=std::move(hand);
    }

    std::vector<Card> Player::getHand() const{
        return this->hand;
    }

    bool Player::getCapacityAvailability() const {
        return this->isCapacityAvailable;
    }

    void Player::setCapacityAvailability(bool availability) {
        this->isCapacityAvailable=availability;
    }

}