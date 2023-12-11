#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine.h"
#include "../../src/shared/state.h"

using namespace ::engine;


BOOST_AUTO_TEST_CASE(TestBuildCommand){
    std::string player1= "player1";
    std::string player2= "player2";
    std::string player3= "player3";
    std::string player4= "player4";

    state::Player plr1 {player1, state::PlayerId::PlayerA};
    state::Player plr2 {player2, state::PlayerId::PlayerB};
    state::Player plr3 {player3, state::PlayerId::PlayerC};
    state::Player plr4 {player4, state::PlayerId::PlayerD};

    state::GameState gameState{std::vector<state::Player>{plr1,plr2,plr3,plr4}};
    gameState.setPlaying(state::PlayerB);

    state::Card card{"1", state::CardType::Religious, 3};

    auto* command= new BuildCommand(state::PlayerA,&card);
    Engine* gameEngine = Engine::getInstance(gameState);
    //Check serialized NIY
    BOOST_CHECK_NO_THROW(command->serialize());

    //Command not executed because not my turn
    BOOST_CHECK_EQUAL(command->check(gameState), false);
    gameState.setPlaying(state::PlayerA);
    //Test all case of non-available command

    //Command not executed because card is not in the hand
    BOOST_CHECK_EQUAL(command->check(gameState), false);

    plr1=gameState.getPlayer(state::PlayerA);

    std::vector<state::Card> hand = std::vector<state::Card>{card};
    plr1.setHand(hand);
    plr1.setBoardOfPlayer(hand);
    gameState.updatePlayer(plr1);
    //Command not executed because already in the board
    BOOST_CHECK_EQUAL(command->check(gameState), false);

    std::vector<state::Card> board = std::vector<state::Card>{};
    plr1.setBoardOfPlayer(board);
    gameState.updatePlayer(plr1);
    //Command not executed because not enough coin
    BOOST_CHECK_EQUAL(command->check(gameState), false);

    plr1.setNumberOfCoins(4);
    gameState.updatePlayer(plr1);
    //True this time
    BOOST_CHECK_EQUAL(command->check(gameState), true);

    gameEngine->addCommand(command);
    gameEngine->executeAllCommands();
    plr1=gameState.getPlayer(state::PlayerA);

    BOOST_CHECK_EQUAL(plr1.getNumberOfCoins(),1);
    BOOST_CHECK_EQUAL(plr1.getHand().size(),0);
    BOOST_CHECK_EQUAL(plr1.getBoardOfPlayer().size(),1);
}

/* vim: set sw=2 sts=2 et : */
