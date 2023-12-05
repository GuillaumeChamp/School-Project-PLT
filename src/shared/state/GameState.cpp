#include "GameState.h"

#include <utility>

namespace state {

    std::vector<Player> GameState::getListOfPlayer () const{
        return this->listOfPlayers;
    }

    void GameState::setCurrentCharacter(CharacterType character) {
        this->currentCharacter=character;
    }

    CharacterType GameState::getCurrentCharacter() const{
        return this->currentCharacter;
    }



    GameState::GameState(std::vector<Player> listOfPlayer) {
        this->listOfPlayers = std::move(listOfPlayer);
        this->currentCharacter= CharacterType::NoCharacter;
        this->crownOwner = PlayerA;
        this->gamePhase = Phase::CHOOSECHARACTER;
        this->playing = NoPlayer;
    }

    void GameState::nextGamePhase() {
        switch (gamePhase) {
            case Phase::CHOOSECHARACTER :
                this->gamePhase = Phase::CALLCHARACTER;
                break;
            case Phase::ENDGAME:
                break;
            case Phase::CALLCHARACTER :
            case STARTGAME:
                this->gamePhase = Phase::CHOOSECHARACTER;
                break;
        }
    }

    Phase GameState::getGamePhase() const{
        return this->gamePhase;
    }

    void GameState::endGame() {
        this->gamePhase=Phase::ENDGAME;
    }

    PlayerId GameState::getCrownOwner() const{
        return this->crownOwner;
    }

    void GameState::setCrownOwner(PlayerId player) {
        this->crownOwner =player;
    }
}