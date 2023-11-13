
#include <boost/test/unit_test.hpp>
#include "render.h"

#include <SFML/Graphics.hpp>

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestSFML)
{
    {
        ::sf::Texture texture;
        BOOST_CHECK(texture.getSize() == ::sf::Vector2<unsigned int> {});

        render::Button button{render::ButtonType::hand,10,20};
        BOOST_CHECK_EQUAL(button.name,render::ButtonType::hand);
        BOOST_CHECK_EQUAL(button.getSurface().getPosition().x,10);
        BOOST_CHECK_EQUAL(button.getSurface().getPosition().y,20);

    }
}

/* vim: set sw=2 sts=2 et : */
