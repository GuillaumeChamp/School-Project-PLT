#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine.h"
#include "../../src/shared/state.h"

using namespace ::engine;


BOOST_AUTO_TEST_CASE(TestBuildCommand){

    state::Player plr1 {"player1", state::PlayerId::PLAYER_A};
    state::Player plr2 {"player2", state::PlayerId::PLAYER_B};
    state::Player plr3 {"player3", state::PlayerId::PLAYER_C};
    state::Player plr4 {"player4", state::PlayerId::PLAYER_D};

    state::GameState gameState{std::vector<state::Player>{plr1,plr2,plr3,plr4}};
    gameState.setPlaying(state::PLAYER_B);

    state::Card card{"1", state::CardType::RELIGIOUS, 3};

    auto* command= new BuildCommand(state::PLAYER_A,&card);
    Engine* gameEngine = Engine::getInstance(gameState);

    //Command not executed because not my turn
    BOOST_CHECK_EQUAL(command->check(gameState), false);
    gameState.setPlaying(state::PLAYER_A);
    //Test all case of non-available command

    //Command not executed because card is not in the hand
    BOOST_CHECK_EQUAL(command->check(gameState), false);

    plr1=gameState.getPlayer(state::PLAYER_A);

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
    plr1=gameState.getPlayer(state::PLAYER_A);

    BOOST_CHECK_EQUAL(plr1.getNumberOfCoins(),1);
    BOOST_CHECK_EQUAL(plr1.getHand().size(),0);
    BOOST_CHECK_EQUAL(plr1.getBoardOfPlayer().size(),1);
}

/* vim: set sw=2 sts=2 et : */
