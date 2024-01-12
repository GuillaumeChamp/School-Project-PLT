#include "GameState.h"

#include <utility>

using namespace state;

GameState::GameState(std::vector<Player> players) {
    this->gamePhase = Phase::START_GAME;
    this->listOfPlayers = std::move(players);
    this->currentCharacter = CharacterType::NO_CHARACTER;
    this->playing = NO_PLAYER;
    this->crownOwner = NO_PLAYER;
    this->killedCharacter = NO_CHARACTER;
    this->robbedCharacter = NO_CHARACTER;
    this->subPhase = Default;
}

GameState::GameState(std::string Name1, std::string Name2, std::string Name3, std::string Name4) {
    this->gamePhase = Phase::START_GAME;
    this->currentCharacter = CharacterType::NO_CHARACTER;
    //création de notre liste de player
    Player playerA{std::move(Name1), PlayerId::PLAYER_A};
    Player playerB{std::move(Name2), PlayerId::PLAYER_B};
    Player playerC{std::move(Name3), PlayerId::PLAYER_C};
    Player playerD{std::move(Name4), PlayerId::PLAYER_D};
    this->listOfPlayers = {playerA, playerB, playerC, playerD};
    this->crownOwner = NO_PLAYER;
    this->playing = NO_PLAYER;
    this->killedCharacter = NO_CHARACTER;
    this->robbedCharacter = NO_CHARACTER;
    this->subPhase = Default;
}

std::vector<Player> GameState::getListOfPlayer() const {
    return this->listOfPlayers;
}

void GameState::setCurrentCharacter(CharacterType character) {
    this->currentCharacter = character;
}

CharacterType GameState::getCurrentCharacter() const {
    return this->currentCharacter;
}

Phase GameState::getGamePhase() const {
    return this->gamePhase;
}

PlayerId GameState::getCrownOwner() const {
    return this->crownOwner;
}

void GameState::setCrownOwner(PlayerId player) {
    this->crownOwner = player;
}

Player GameState::getPlayer(PlayerId playerId) const {
    for (const Player &player: this->listOfPlayers) {
        if (player.getIdOfPlayer() == playerId) {
            return player;
        }
    }
    throw std::exception();
}

PlayerId GameState::getPlaying() const {
    return this->playing;
}

void GameState::setPlaying(PlayerId playerId) {
    this->playing = playerId;
}

std::vector<CharacterType> GameState::getAvailableCharacter() const {
    return this->availableCharacter;
}

void GameState::setAvailableCharacter(std::vector<CharacterType> listOfCharacter) {
    this->availableCharacter.clear();
    this->availableCharacter = std::move(listOfCharacter);
}

void GameState::updatePlayer(Player &player) {
    for (auto &p: listOfPlayers) {
        if (player.getIdOfPlayer() == p.getIdOfPlayer()) {
            p = player;
            return;
        }
    }
    throw std::exception();
}

std::list<Card> GameState::getStack() const {
    return this->stack;
}

CharacterType GameState::getKilledCharacter() const {
    return this->killedCharacter;
}

CharacterType GameState::getRobbedCharacter() const {
    return this->robbedCharacter;
}

std::vector<Card> GameState::getDrawableCards() const {
    return this->drawableCards;
}

SubPhase GameState::getSubPhase() const {
    return this->subPhase;
}

void GameState::setStack(std::list<Card> newStack) {
    this->stack.clear();
    this->stack = std::move(newStack);
}

void GameState::setKilledCharacter(CharacterType character) {
    this->killedCharacter = character;
}

void GameState::setDrawableCards(std::vector<Card> listOfDrawableCards) {
    this->drawableCards.clear();
    this->drawableCards = std::move(listOfDrawableCards);
}

void GameState::setRobbedCharacter(CharacterType character) {
    this->robbedCharacter = character;
}

void GameState::setGamePhase(Phase newPhase) {
    this->gamePhase = newPhase;
}

void GameState::setSubPhase(SubPhase newSubPhase) {
    this->subPhase = newSubPhase;
}


PlayerId GameState::getPlayerIdByCharacter(CharacterType character) {
    for (const auto& p : listOfPlayers){
        if (p.getCharacter()==character)
            return p.getIdOfPlayer();
    }
    return NO_PLAYER;
}
