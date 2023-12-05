#include "GameState.h"

#include <utility>

namespace state {

    std::vector<Player> GameState::getListOfPlayer (){
        return this->listOfPlayers;
    }

    int GameState::getNbCardToDraw () const{
        return this->nbOfCardToDraw;
    }


    void GameState::setNbCardToDraw (int nbCard){
        this->nbOfCardToDraw = nbCard;
    }

    void GameState::setCurrentCharacter(CharacterType character) {
        this->currentCharacter=character;
    }

    CharacterType GameState::getCurrentCharacter() const{
        return this->currentCharacter;
    }



    GameState::GameState(std::vector<Player> listOfPlayer) {
        this->listOfPlayers=std::move(listOfPlayer);
        this->nbOfCardToDraw=52;
        this->currentCharacter= CharacterType::NoCharacter;
        this->crownOwner = PlayerA;
        this->gamePhase = GamePhase::DrawCharacters;
    }

    void GameState::nextGamePhase() {
        switch (gamePhase) {
            case GamePhase::DrawCharacters :
                this->gamePhase = GamePhase::PlayTurn;
                break;
            case GamePhase::EndOfGame:
                break;
            case GamePhase::PlayTurn :
                this->gamePhase = GamePhase::DrawCharacters;
                break;
        }
    }

    GamePhase GameState::getGamePhase() const{
        return this->gamePhase;
    }

    void GameState::endGame() {
        this->gamePhase=GamePhase::EndOfGame;
    }

    PlayerId GameState::getCrownOwner() const{
        return this->crownOwner;
    }

    void GameState::setCrownOwner(PlayerId player) {
        this->crownOwner =player;
    }


}