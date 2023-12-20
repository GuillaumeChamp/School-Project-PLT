//
// Created by guillaume on 12/19/23.
//
#include "StateSerializer.h"

#define PLAYER "players"
#define NAME "name"


namespace state {

    Json::Value state::StateSerializer::serialize(GameState &state) {
        Json::Value json;
        Player playerA = state.getPlayer(PLAYER_A);
        json[PLAYER]["playerA"][NAME] = playerA.getNameOfPlayer();

        playerA = state.getPlayer(PLAYER_B);
        json[PLAYER]["playerB"][NAME] = playerA.getNameOfPlayer();

        playerA = state.getPlayer(PLAYER_C);
        json[PLAYER]["playerC"][NAME] = playerA.getNameOfPlayer();

        playerA = state.getPlayer(PLAYER_D);
        json[PLAYER]["playerD"][NAME] = playerA.getNameOfPlayer();

        json["playing"] = state.getPlaying();
        return json;
    }

    GameState state::StateSerializer::unserialize(Json::Value &data) {
        Player player0{data[PLAYER]["playerA"].get(NAME, "joueur 1").asString(), PlayerId::PLAYER_A};
        Player player1{data[PLAYER]["playerB"].get(NAME, "joueur 2").asString(), PlayerId::PLAYER_B};
        Player player2{data[PLAYER]["playerC"].get(NAME, "joueur 3").asString(), PlayerId::PLAYER_C};
        Player player3{data[PLAYER]["playerD"].get(NAME, "joueur 4").asString(), PlayerId::PLAYER_D};

        GameState object{std::vector<Player>{player0, player1, player2, player3}};
        object.setPlaying(static_cast<PlayerId>(data.get("playing", NO_PLAYER).asInt()));

        return object;
    }

}