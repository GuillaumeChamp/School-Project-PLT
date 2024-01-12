//
// Created by guillaume on 1/10/24.
//
#include "state.h"
#include "engine.h"
#include <thread>
#include "ApiManager.h"
#ifndef PLT_ACTIVEGAME_H
#define PLT_ACTIVEGAME_H

#define IHM_TEMP_FILE "/tmp/cit_ihm.txt"

class ActiveGame {
private:
    std::shared_ptr<state::GameState> game;
    state::PlayerId myId;
    std::string myName;
public:
    ActiveGame(state::PlayerId id,const std::string& name,bool& notif);
    ~ActiveGame();

    static void networkLookup(bool& notif,const std::string& name,state::PlayerId playerId);
    std::shared_ptr<state::GameState> getGame() const;
};


#endif //PLT_ACTIVEGAME_H
