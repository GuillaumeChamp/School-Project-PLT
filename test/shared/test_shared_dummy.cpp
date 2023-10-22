#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/ActivePlayer.h"
#include "../../src/shared/state/Player.h"
#include "../../src/shared/state/Card.h"
#include "../../src/shared/state/GameState.h"
#include "../../src/shared/state.h"

using namespace ::state;


BOOST_AUTO_TEST_CASE(TestState)
{
  {
    Player plr ;
    plr.setNumberOfCards(4);
    BOOST_CHECK_EQUAL(plr.getNumberOfCards(),4);
    plr.setNumberOfCoins(5);
    BOOST_CHECK_EQUAL(plr.getNumberOfCoins(),5);
    std::vector<Card> board;
    plr.setBoardOfPlayer(board);
    BOOST_CHECK_EQUAL((plr.getBoardOfPlayer()).size(),board.size());

    GameState gamestate;
    gamestate.setNbCardToDraw(3);
    BOOST_CHECK_EQUAL(gamestate.getNbCardToDraw(),3);
    Player player;
    gamestate.setCrownOwner(player);
    BOOST_CHECK_EQUAL((gamestate.getCrownOwner()).getNameOfPlayer(),player.getNameOfPlayer());

    Card card;
    BOOST_CHECK_EQUAL(card.getNameOfCard(), std::string());
    card.getColorOfCard();
    BOOST_CHECK_EQUAL(card.getCostOfCard(), 0);

    ActivePlayer ex {};
    BOOST_CHECK_EQUAL(ex.getNameOfPlayer(), std::string());
    std::vector<Card> hand;
    ex.setHand(hand);
    BOOST_CHECK_EQUAL((ex.getHand()).size(), hand.size());
  }
}

/* vim: set sw=2 sts=2 et : */
