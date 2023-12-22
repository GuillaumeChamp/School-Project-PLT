#include "GameState.h"

#include <utility>

namespace state {

    GameState::GameState(std::vector<Player> players) {
        this->gamePhase = Phase::START_GAME;
        this->listOfPlayers = std::move(players);
        this->currentCharacter = CharacterType::NO_CHARACTER;
    }

    GameState::GameState(std::string Name1, std::string Name2, std::string Name3, std::string Name4) {
        this->gamePhase = Phase::START_GAME;
        this->currentCharacter = CharacterType::NO_CHARACTER;
        //création de notre liste de player
        Player playerA{Name1, PlayerId::PLAYER_A};
        Player playerB{Name2, PlayerId::PLAYER_B};
        Player playerC{Name3, PlayerId::PLAYER_C};
        Player playerD{Name4, PlayerId::PLAYER_D};
        this->listOfPlayers = {playerA, playerB, playerC, playerD};

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
        for (int i = 0; i < (int) listOfPlayers.size(); i++) {
            if (player.getIdOfPlayer() == listOfPlayers[i].getIdOfPlayer()) {
                listOfPlayers[i] = player;
                return;
            }
        }
        throw std::exception();
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

    std::vector<Card> GameState::getDrawableCards() const {
        return this->drawableCards;
    }

    void GameState::setStack(std::vector<Card> stack) {
        this->stack.clear();
        this->stack = std::move(stack);
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


}