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
    state::GameState* game;
    static state::PlayerId myId;
    std::string myName;
public:
    ActiveGame(state::PlayerId id,std::string name,bool& notif);
    ~ActiveGame();

    static void networkLookup(bool& notif,std::string name);
    state::GameState *getGame() const;
};


#endif //PLT_ACTIVEGAME_H
