#include "GameState.h"

#include <utility>

namespace state {

    GameState::GameState(std::vector<Player> listOfPlayer) {
        this->listOfPlayers = std::move(listOfPlayer);
        this->currentCharacter= CharacterType::NO_CHARACTER;
        this->crownOwner = PLAYER_A;
        this->gamePhase = Phase::CHOOSE_CHARACTER;
        this->playing = NO_PLAYER;
        this->killedCharacter = NO_CHARACTER;
        this->robbedCharacter = NO_CHARACTER;
    }

    std::vector<Player> GameState::getListOfPlayer () const{
        return this->listOfPlayers;
    }

    void GameState::setCurrentCharacter(CharacterType character) {
        this->currentCharacter=character;
    }

    CharacterType GameState::getCurrentCharacter() const{
        return this->currentCharacter;
    }

    Phase GameState::getGamePhase() const{
        return this->gamePhase;
    }

    PlayerId GameState::getCrownOwner() const{
        return this->crownOwner;
    }

    void GameState::setCrownOwner(PlayerId player) {
        this->crownOwner =player;
    }

    Player GameState::getPlayer(PlayerId playerId) const {
        for(const Player& player : this->listOfPlayers){
            if (player.getIdOfPlayer()==playerId){
                return player;
            }
        }
        throw std::exception();
    }

    PlayerId GameState::getPlaying() const {
        return this->playing;
    }

    void GameState::setPlaying(PlayerId playerId) {
        this->playing=playerId;
    }

    std::vector<CharacterType> GameState::getAvailableCharacter () const{
        return this->availableCharacter;
    }

    void GameState::setAvailableCharacter (std::vector<CharacterType> listOfCharacter){
        this->availableCharacter.clear();
        this->availableCharacter=std::move(listOfCharacter);
    }

    std::vector<Card> GameState::getDrawableCards() {
        return this->drawableCards;
    }

    void GameState::setDrawableCards (std::vector<Card> listOfDrawableCards){
        this->drawableCards=listOfDrawableCards;
    }

    void GameState::updatePlayer(Player& player) {
        for (int i=0;i<listOfPlayers.size();i++){
            if (player.getIdOfPlayer()==listOfPlayers[i].getIdOfPlayer()){
                listOfPlayers[i]=player;
                return;
            }
        }
    }

    std::vector<Card> GameState::getStack() const {
        return this->stack;
    }

    CharacterType GameState::getKilledCharacter() const {
        return this->killedCharacter;
    }

    CharacterType GameState::getRobbedCharacter() const {
        return this->robbedCharacter;
    }

    std::vector<Card> GameState::getDrawableCards() const{
        return this->drawableCards;
    }

    void GameState::setStack(std::vector<Card> stack) {
        this->stack.clear();
        this->stack=std::move(stack);
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
        this->gamePhase=newPhase;
    }
}