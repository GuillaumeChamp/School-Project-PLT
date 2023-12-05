#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine.h"
#include "../../src/shared/state.h"

using namespace ::engine;


BOOST_AUTO_TEST_CASE(TestEngine){
    state::Player plr1 {"player1", state::PlayerId::PlayerA};
    state::Player plr2 {"player2", state::PlayerId::PlayerB};
    state::Player plr3 {"player3", state::PlayerId::PlayerC};
    state::Player plr4 {"player4", state::PlayerId::PlayerD};

    state::GameState gameState{std::vector<state::Player>{plr1,plr2,plr3,plr4}};

    state::Card card{"1", state::CardType::Military, 2};
    BuildCommand buildCommand{state::PlayerA,&card};
}

/* vim: set sw=2 sts=2 et : */
