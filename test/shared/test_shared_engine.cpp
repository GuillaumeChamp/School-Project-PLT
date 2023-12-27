#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine.h"

using namespace ::engine;


struct F {
    F() : gameState("player1",
                    "player2",
                    "player3",
                    "player4") { BOOST_TEST_MESSAGE("setup fixture"); }

    ~F() { BOOST_TEST_MESSAGE("teardown fixture"); }

    state::GameState gameState;
};

//____________________________________________________________________________//

BOOST_FIXTURE_TEST_SUITE(CommandTestCase, F)
    BOOST_AUTO_TEST_CASE(ShouldCommandBeCovered){
        Command c{};
        BOOST_CHECK_NO_THROW(c.execute(gameState));
 }

    BOOST_AUTO_TEST_CASE(TestBuildCommand) {

        gameState.setPlaying(state::PLAYER_B);

        state::Card card{"1", state::CardType::RELIGIOUS, 3};

        auto *command = new BuildCommand(state::PLAYER_A, card);
        BOOST_CHECK_EQUAL(command->getCommandTypeId(),CommandTypeId::BUILD);

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

        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();
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
        BOOST_CHECK_EQUAL(gameState.getDrawableCards().size(), 0);
        BOOST_CHECK_EQUAL(command->getCommandTypeId(),CommandTypeId::DRAW_CARD);

        //Command not executed because not my turn
        BOOST_CHECK_EQUAL(command->check(gameState), false);
        gameState.setPlaying(state::PlayerId::PLAYER_A);

        //Command not executed because draw is not available
        BOOST_CHECK_EQUAL(command->check(gameState), false);

        plr1.setDrawAvailability(true);
        gameState.updatePlayer(plr1);

        BOOST_CHECK_EQUAL(command->check(gameState), true);
        BOOST_CHECK_EQUAL(gameState.getStack().size(), 0);

        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getDrawableCards().size(), 2);
        BOOST_CHECK_EQUAL(gameState.getStack().size(), 63);

        command = new DrawCommand(state::PlayerId::PLAYER_A, 3);
        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getDrawableCards().size(), 3);
        BOOST_CHECK_EQUAL(gameState.getStack().size(), 60);

    }

    BOOST_AUTO_TEST_CASE(TestEndOfTurnCommand) {
        state::Player plr1 = gameState.getPlayer(state::PLAYER_A);
        gameState.setCrownOwner(state::PLAYER_A);
        gameState.setPlaying(state::PLAYER_A);
        gameState.setGamePhase(state::CHOOSE_CHARACTER);
        gameState.setCurrentCharacter(state::NO_CHARACTER);

        auto *command = new EndOfTurnCommand(state::PlayerId::PLAYER_A);
        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_A);

        BOOST_CHECK_EQUAL(command->check(gameState), true);

        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();
        plr1.setCharacter(state::KING);
        gameState.updatePlayer(plr1);

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_B);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_B);
        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_C);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_C);
        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_D);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_D);
        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();

        //still player D turn because he is the last to play (A hold crown)
        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_A);

    }

BOOST_AUTO_TEST_SUITE_END()

