//
// Created by guillaume on 12/19/23.
//
#include "StateSerializer.h"

#define PLAYER "players"
#define NAME "name"
#define CHARACTER "character"
#define COIN "coin"
#define HAND "hand"
#define BOARD "board"
#define COST "cost"
#define COLOR "color"
#define PLAYING "playing"
#define STACK "stack"
#define KILL "killedCharacter"
#define ROB "robbedCharacter"
#define CROWN "crownOwner"
#define CURRENT "currentCharacter"
#define PHASE "gamePhase"
#define AVAILABLE "availableCharacter"
#define DRAW "drawableCards"


namespace state {

    Json::Value state::StateSerializer::serialize(GameState &state) {
        Json::Value json;
        Player playerA = state.getPlayer(PLAYER_A);
        serializePlayer(playerA, json);

        playerA = state.getPlayer(PLAYER_B);
        serializePlayer(playerA, json);

        playerA = state.getPlayer(PLAYER_C);
        serializePlayer(playerA, json);

        playerA = state.getPlayer(PLAYER_D);
        serializePlayer(playerA, json);

        json[PLAYING] = state.getPlaying();
        json[KILL] = state.getKilledCharacter();
        json[ROB] = state.getRobbedCharacter();
        json[CROWN] = state.getCrownOwner();
        json[CURRENT] = state.getCurrentCharacter();
        json[PHASE] = state.getGamePhase();

        std::vector<Card> cards = state.getStack();
        for (int i = 0; i < (int) cards.size(); i++) {
            json[STACK][i][NAME] = cards[i].getNameOfCard();
            json[STACK][i][COLOR] = cards[i].getColorOfCard();
            json[STACK][i][COST] = cards[i].getCostOfCard();
        }

        cards = state.getDrawableCards();
        for (int i = 0; i < (int) cards.size(); i++) {
            json[DRAW][i][NAME] = cards[i].getNameOfCard();
            json[DRAW][i][COLOR] = cards[i].getColorOfCard();
            json[DRAW][i][COST] = cards[i].getCostOfCard();
        }

        std::vector<CharacterType> available = state.getAvailableCharacter();
        for (int i = 0; i < (int) available.size(); i++) {
            json[AVAILABLE][i] = available[i];
        }
        return json;
    }

    GameState state::StateSerializer::deserialize(Json::Value &data) {
        Player player0 = deserializePlayer(data, PlayerId::PLAYER_A);
        Player player1 = deserializePlayer(data, PlayerId::PLAYER_B);
        Player player2 = deserializePlayer(data, PlayerId::PLAYER_C);
        Player player3 = deserializePlayer(data, PlayerId::PLAYER_D);

        GameState object{std::vector<Player>{player0, player1, player2, player3}};
        object.setPlaying(static_cast<PlayerId>(data.get(PLAYING, NO_PLAYER).asInt()));

        object.setRobbedCharacter(static_cast<CharacterType>(data[ROB].asInt()));
        object.setKilledCharacter(static_cast<CharacterType>(data[KILL].asInt()));
        object.setCrownOwner(static_cast<PlayerId>(data[CROWN].asInt()));
        object.setCurrentCharacter(static_cast<CharacterType>(data[CURRENT].asInt()));
        object.setGamePhase(static_cast<Phase>(data[PHASE].asInt()));

        //stack
        std::vector<Card> stack;
        int i = 0;
        while (!data[STACK][i].isNull()) {
            std::string cardString = data[STACK][i][NAME].asString();
            int cost = data[STACK][i][COST].asInt();
            int color = data[STACK][i][COLOR].asInt();
            stack.emplace_back(cardString, static_cast<state::CardType>(color), cost);
            i++;
        }
        object.setStack(stack);

        std::vector<Card> draw;
        i = 0;
        while (!data[DRAW][i].isNull()) {
            std::string cardString = data[DRAW][i][NAME].asString();
            int cost = data[DRAW][i][COST].asInt();
            int color = data[DRAW][i][COLOR].asInt();
            stack.emplace_back(cardString, static_cast<state::CardType>(color), cost);
            i++;
        }
        object.setDrawableCards(draw);

        std::vector<CharacterType> characters;
        while (!data[AVAILABLE][i].isNull()) {
            characters.push_back(static_cast<state::CharacterType>(data[AVAILABLE][i].asInt()));
            i++;
        }
        object.setAvailableCharacter(characters);
        return object;
    }

    Player StateSerializer::deserializePlayer(Json::Value &data, PlayerId id) {
        std::string name = data[PLAYER][id][NAME].asString();
        Player player{name, id};
        player.setCharacter(static_cast<CharacterType>(data[PLAYER][id][CHARACTER].asInt()));
        player.setNumberOfCoins(data[PLAYER][id][COIN].asInt());

        std::vector<Card> card;
        int i = 0;
        while (!data[PLAYER][id][HAND][i].isNull()) {
            std::string cardString = data[PLAYER][id][HAND][i][NAME].asString();
            int cost = data[PLAYER][id][HAND][i][COST].asInt();
            int color = data[PLAYER][id][HAND][i][COLOR].asInt();
            card.emplace_back(cardString, static_cast<state::CardType>(color), cost);
            i++;
        }
        player.setHand(card);

        i = 0;
        std::vector<Card> board;

        while (!data[PLAYER][id][BOARD][i].isNull()) {
            std::string cardString = data[PLAYER][id][BOARD][i][NAME].asString();
            int cost = data[PLAYER][id][BOARD][i][COST].asInt();
            int color = data[PLAYER][id][BOARD][i][COLOR].asInt();
            board.emplace_back(name, static_cast<state::CardType>(color), cost);
            i++;
        }
        player.setBoardOfPlayer(board);
        return player;
    }

    void StateSerializer::serializePlayer(Player &player, Json::Value &data) {
        const int id = player.getIdOfPlayer();
        data[PLAYER][id][NAME] = player.getNameOfPlayer();
        data[PLAYER][id][CHARACTER] = player.getCharacter();
        data[PLAYER][id][COIN] = player.getNumberOfCoins();

        std::vector<Card> cards = player.getHand();
        for (int i = 0; i < (int) cards.size(); i++) {
            data[PLAYER][id][HAND][i][NAME] = (cards[i].getNameOfCard());
            data[PLAYER][id][HAND][i][COLOR] = (cards[i].getColorOfCard());
            data[PLAYER][id][HAND][i][COST] = (cards[i].getCostOfCard());
        }

        cards = player.getBoardOfPlayer();
        for (int i = 0; i < (int) cards.size(); i++) {
            data[PLAYER][id][BOARD][i][NAME] = (cards[i].getNameOfCard());
            data[PLAYER][id][BOARD][i][COLOR] = (cards[i].getColorOfCard());
            data[PLAYER][id][BOARD][i][COST] = (cards[i].getCostOfCard());
        }
    }

}