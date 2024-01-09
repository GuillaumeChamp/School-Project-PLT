#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine.h"

using namespace ::engine;

#define STACK_SIZE 66
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

        auto *command = new DrawCommand(state::PlayerId::PLAYER_A);
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
        BOOST_CHECK_EQUAL(gameState.getStack().size(), STACK_SIZE);

        state::Card cardWonder{"22", state::CardType::WONDER, 5};
        std::vector<state::Card> newBoard;
        newBoard.push_back(cardWonder);
        plr1.setBoardOfPlayer(newBoard);
        command = new DrawCommand(state::PlayerId::PLAYER_A);
        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getDrawableCards().size(), 3);
        BOOST_CHECK_EQUAL(gameState.getStack().size(), STACK_SIZE-3);

    }

    BOOST_AUTO_TEST_CASE(TestEndOfTurnCommand) {
        state::Player playerC=gameState.getPlayer(state::PlayerId::PLAYER_C);
        playerC.setNumberOfCoins(10);
        gameState.updatePlayer(playerC);
        state::Player playerD=gameState.getPlayer(state::PlayerId::PLAYER_D);
        playerD.setNumberOfCoins(5);
        gameState.updatePlayer(playerD);
        
        gameState.setCrownOwner(state::PLAYER_B);
        gameState.setPlaying(state::PLAYER_B);
        gameState.setGamePhase(state::CHOOSE_CHARACTER);
        gameState.setCurrentCharacter(state::NO_CHARACTER);
        gameState.setAvailableCharacter({state::CharacterType::ASSASSIN,
                                             state::CharacterType::THIEF,
                                             state::CharacterType::MAGICIAN,
                                             state::CharacterType::KING,
                                             state::CharacterType::BISHOP,
                                             state::CharacterType::MERCHANT,
                                             state::CharacterType::ARCHITECT,
                                             state::CharacterType::WARLORD});
        

        
        auto* command = new EndOfTurnCommand(state::PlayerId::PLAYER_B);
        auto* chooseCharacter = new ChooseCharacterCommand(state::PlayerId::PLAYER_B,state::CharacterType::KING);
        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_B);
        BOOST_CHECK_EQUAL(command->check(gameState), true);
        Engine::getInstance(gameState).addCommand(chooseCharacter);
        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_C);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_C);
        chooseCharacter = new ChooseCharacterCommand(state::PlayerId::PLAYER_C,state::CharacterType::WARLORD);
        Engine::getInstance(gameState).addCommand(chooseCharacter);
        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_D);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_D);
        chooseCharacter = new ChooseCharacterCommand(state::PlayerId::PLAYER_D,state::CharacterType::THIEF);
        Engine::getInstance(gameState).addCommand(chooseCharacter);
        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_A);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_A);
        chooseCharacter = new ChooseCharacterCommand(state::PlayerId::PLAYER_A,state::CharacterType::MERCHANT);
        Engine::getInstance(gameState).addCommand(chooseCharacter);
        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();

        //Check if the switch pahse is OK
        BOOST_CHECK_EQUAL(gameState.getGamePhase(), state::Phase::CALL_CHARACTER);

        //Check for the nextplayers during this phase
        //PlayerD=Assasin--PlayerB=King--PlayerA=Merchant--PlayerC=Warlord
        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_D);
        gameState.setRobbedCharacter(state::CharacterType::WARLORD);
        //PlayerC will be roobed by PlayerD
        gameState.setKilledCharacter(state::CharacterType::MERCHANT);
        //PlayerA will pass his turn
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_D);
        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_B);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_B);
        gameState.setCrownOwner(state::PlayerId::PLAYER_B);
        //at the end of this phase B will be the first player
        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();

        //playerA is supposed to be killed because he is the MERCHANT
        //It's supposed to be PlayerC turn, but he got robbed by D

        BOOST_CHECK_EQUAL(gameState.getPlayer(state::PlayerId::PLAYER_C).getNumberOfCoins(),0);
        BOOST_CHECK_EQUAL(gameState.getPlayer(state::PlayerId::PLAYER_D).getNumberOfCoins(),15);

        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_C);
        command = new EndOfTurnCommand(state::PlayerId::PLAYER_C);
        Engine::getInstance(gameState).addCommand(command);
        Engine::getInstance(gameState).executeAllCommands();
        
         //Check if the switch phase is OK
        BOOST_CHECK_EQUAL(gameState.getGamePhase(), state::Phase::CHOOSE_CHARACTER);
        BOOST_CHECK_EQUAL(gameState.getPlaying(), state::PlayerId::PLAYER_B);
        
    }

BOOST_AUTO_TEST_SUITE_END()

