#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/ActivePlayer.h"
#include "../../src/shared/state.h"

using namespace ::state;


BOOST_AUTO_TEST_CASE(TestState)
{
  {
    ActivePlayer ex {};
    BOOST_CHECK_EQUAL(ex.getNameOfPlayer(), std::string());

    Player plr ;
    plr.setNumberOfCards(4)
    BOOST_CHECK_EQUAL(plr.getNumberOfCards,4)
    plr.setNumberOfCoins(5)
    BOOST_CHECK_EQUAL(plr.getNumberOfCoins,5)
  }
}

/* vim: set sw=2 sts=2 et : */
