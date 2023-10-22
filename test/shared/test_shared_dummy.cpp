#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/ActivePlayer.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestExemple)
{
  {
    ActivePlayer ex {};
    BOOST_CHECK_EQUAL(ex.getNameOfPlayer(), std::string());
  }
}

/* vim: set sw=2 sts=2 et : */
