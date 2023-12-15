#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine.h"
#include "../../src/shared/state.h"

using namespace ::engine;


struct F {
    F() : gameState({{"player1", state::PlayerId::PLAYER_A},
                     {"player2", state::PlayerId::PLAYER_B},
                     {"player3", state::PlayerId::PLAYER_C},
                     {"player4", state::PlayerId::PLAYER_D}}) { BOOST_TEST_MESSAGE("setup fixture"); }

    ~F() { BOOST_TEST_MESSAGE("teardown fixture"); }

    state::GameState gameState;
};

//____________________________________________________________________________//

BOOST_FIXTURE_TEST_SUITE(s, F)

    BOOST_AUTO_TEST_CASE(TestBuildCommand) {

        gameState.setPlaying(state::PLAYER_B);

        state::Card card{"1", state::CardType::RELIGIOUS, 3};

        auto *command = new BuildCommand(state::PLAYER_A, &card);
        Engine *gameEngine = Engine::getInstance(gameState);
        //Check serialized NIY
        BOOST_CHECK_NO_THROW(command->serialize());

        //Command not executed because not my turn
        BOOST_CHECK_EQUAL(command->check(gameState), false);
        gameState.setPlaying(state::PLAYER_A);
        //Test all case of non-available command

        //Command not executed because card is not in the hand
        BOOST_CHECK_EQUAL(command->check(gameState), false);

        state::Player plr1 = gameState.getPlayer(state::PLAYER_A);

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
        plr1 = gameState.getPlayer(state::PLAYER_A);

        BOOST_CHECK_EQUAL(plr1.getNumberOfCoins(), 1);
        BOOST_CHECK_EQUAL(plr1.getHand().size(), 0);
        BOOST_CHECK_EQUAL(plr1.getBoardOfPlayer().size(), 1);
    }

    BOOST_AUTO_TEST_CASE(TestDrawCommand) {
        state::Player plr1 = gameState.getPlayer(state::PLAYER_A);

        plr1.setDrawAvailability(false);

        gameState.setPlaying(state::PLAYER_B);

        auto *command = new DrawCommand(state::PlayerId::PLAYER_A, 2);
        Engine *gameEngine = Engine::getInstance(gameState);
        BOOST_CHECK_EQUAL(gameState.getDrawableCards().size(), 0);
        //Check serialized NIY
        BOOST_CHECK_NO_THROW(command->serialize());

        //Command not executed because not my turn
        BOOST_CHECK_EQUAL(command->check(gameState), false);
        gameState.setPlaying(state::PlayerId::PLAYER_A);

        //Command not executed because draw is not available
        BOOST_CHECK_EQUAL(command->check(gameState), false);

        plr1.setDrawAvailability(true);
        gameState.updatePlayer(plr1);

        BOOST_CHECK_EQUAL(command->check(gameState), true);
        BOOST_CHECK_EQUAL(gameState.getStack().size(), 0);

        gameEngine->addCommand(command);
        gameEngine->executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getDrawableCards().size(), 2);
        BOOST_CHECK_EQUAL(gameState.getStack().size(), 63);

        command = new DrawCommand(state::PlayerId::PLAYER_A, 3);
        gameEngine->addCommand(command);
        gameEngine->executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getDrawableCards().size(), 3);
        BOOST_CHECK_EQUAL(gameState.getStack().size(), 60);

    }

    BOOST_AUTO_TEST_CASE(TestEndOfTurnCommand) {
        state::Player plr1 = gameState.getPlayer(state::PLAYER_A);

        gameState.setPlaying(state::PLAYER_A);

        auto *command = new EndOfTurnCommand(state::PlayerId::PLAYER_A);
        Engine *gameEngine = Engine::getInstance(gameState);
        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_A);
        //Check serialized NIY
        BOOST_CHECK_NO_THROW(command->serialize());

        BOOST_CHECK_EQUAL(command->check(gameState), true);
        BOOST_CHECK_EQUAL(gameState.getStack().size(), 0);

        gameEngine->addCommand(command);
        gameEngine->executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_B);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_B);
        gameEngine->addCommand(command);
        gameEngine->executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_C);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_C);
        gameEngine->addCommand(command);
        gameEngine->executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_D);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_D);
        gameEngine->addCommand(command);
        gameEngine->executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_A);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_A);
        gameEngine->addCommand(command);
        gameEngine->executeAllCommands();
    }

BOOST_AUTO_TEST_SUITE_END()

