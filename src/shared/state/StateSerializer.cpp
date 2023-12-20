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


namespace state {

    Json::Value state::StateSerializer::serialize(GameState &state) {
        Json::Value json;
        Player playerA = state.getPlayer(PLAYER_A);
        serializePlayer(playerA,json);

        playerA = state.getPlayer(PLAYER_B);
        serializePlayer(playerA,json);

        playerA = state.getPlayer(PLAYER_C);
        serializePlayer(playerA,json);

        playerA = state.getPlayer(PLAYER_D);
        serializePlayer(playerA,json);

        json["playing"] = state.getPlaying();
        return json;
    }

    GameState state::StateSerializer::deserialize(Json::Value &data) {
        Player player0 = deserializePlayer(data,PlayerId::PLAYER_A);
        Player player1 = deserializePlayer(data,PlayerId::PLAYER_B);
        Player player2 = deserializePlayer(data,PlayerId::PLAYER_C);
        Player player3 = deserializePlayer(data,PlayerId::PLAYER_D);

        GameState object{std::vector<Player>{player0, player1, player2, player3}};
        object.setPlaying(static_cast<PlayerId>(data.get("playing", NO_PLAYER).asInt()));

        return object;
    }

    Player StateSerializer::deserializePlayer(Json::Value &data,PlayerId id) {
        std::string name = data[PLAYER][id][NAME].asString();
        Player player{name,id};
        player.setCharacter(static_cast<CharacterType>(data[PLAYER][id][CHARACTER].asInt()));
        player.setNumberOfCoins(data[PLAYER][id][COIN].asInt());

        std::vector<Card> card;
        for (int i =0;i<30;i++){
            if (data[PLAYER][id][HAND][i].isNull()){
                break;
            }
            std::string cardString = data[PLAYER][id][HAND][i][NAME].asString();
            int cost = data[PLAYER][id][HAND][i][COST].asInt();
            int color = data[PLAYER][id][HAND][i][COLOR].asInt();
            card.emplace_back(name,static_cast<state::CardType>(color),cost);
        }
        player.setHand(card);

        std::vector<Card> board;
        for (int i =0;i<30;i++){
            if (data[PLAYER][id][BOARD][i].isNull()){
                break;
            }
            std::string cardString = data[PLAYER][id][BOARD][i][NAME].asString();
            int cost = data[PLAYER][id][BOARD][i][COST].asInt();
            int color = data[PLAYER][id][BOARD][i][COLOR].asInt();
            board.emplace_back(name,static_cast<state::CardType>(color),cost);
        }
        player.setBoardOfPlayer(board);
        return player;
    }

    void StateSerializer::serializePlayer(Player &player, Json::Value &data) {
        const int id= player.getIdOfPlayer();
        data[PLAYER][id][NAME] = player.getNameOfPlayer();
        data[PLAYER][id][CHARACTER] = player.getCharacter();
        data[PLAYER][id][COIN] = player.getNumberOfCoins();

        std::vector<Card> cards = player.getHand();
        for(int i=0;i<cards.size();i++){
            data[PLAYER][id][HAND][i][NAME] = (cards[i].getNameOfCard());
            data[PLAYER][id][HAND][i][COLOR] = (cards[i].getColorOfCard());
            data[PLAYER][id][HAND][i][COST] = (cards[i].getCostOfCard());
        }

        cards = player.getBoardOfPlayer();
        for(int i=0;i<cards.size();i++){
            data[PLAYER][id][BOARD][i][NAME] = (cards[i].getNameOfCard());
            data[PLAYER][id][BOARD][i][COLOR] = (cards[i].getColorOfCard());
            data[PLAYER][id][BOARD][i][COST] = (cards[i].getCostOfCard());

        }
    }

}