#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine.h"
#include "../../src/shared/state.h"

using namespace ::engine;


BOOST_AUTO_TEST_CASE(TestEngine){
    std::string player1= "player1";
    std::string player2= "player2";
    std::string player3= "player3";
    std::string player4= "player4";

    state::Player plr1 {player1, state::PlayerId::PlayerA};
    state::Player plr2 {player2, state::PlayerId::PlayerB};
    state::Player plr3 {player3, state::PlayerId::PlayerC};
    state::Player plr4 {player4, state::PlayerId::PlayerD};

    state::GameState gameState{std::vector<state::Player>{plr1,plr2,plr3,plr4}};

    state::Card card{"1", state::CardType::Religious, 1};

    plr1.setNumberOfCoins(10);
    gameState.updatePlayer(plr1);

    auto* command= new BuildCommand(state::PlayerA,&card);
    Engine gameEngine(gameState);
    //build->execute(gameState);
    gameEngine.addCommand(command);
    gameEngine.executeAllCommands();
    plr1=gameState.getPlayer(state::PlayerA);
    BOOST_CHECK_EQUAL(plr1.getNumberOfCoins(),9);
    BOOST_CHECK_EQUAL(plr1.getHand().size(),0);
    BOOST_CHECK_EQUAL(plr1.getBoardOfPlayer().size(),1);
}

/* vim: set sw=2 sts=2 et : */
