
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

        BOOST_CHECK_EQUAL(render::IHMState::getInstance()->hoverCard, nullptr);
        BOOST_CHECK_EQUAL(render::IHMState::getInstance()->hoverButton, nullptr);
        BOOST_CHECK_EQUAL(render::IHMState::getInstance()->isHandDisplayed, false);
        BOOST_CHECK_EQUAL(render::IHMState::getInstance()->isHelpDisplayed, false);

        state::Player playerA {"player1", state::PlayerId::PlayerA};
        state::Player playerB {"player2", state::PlayerId::PlayerB};
        state::Player playerC {"player3", state::PlayerId::PlayerC};
        state::Player playerD {"player4", state::PlayerId::PlayerD};

        state::GameState gameState {std::vector<state::Player>{playerA,playerB,playerC,playerD}};
        render::Scene scene{render::SceneId::PlayerA,&gameState};

        sf::RenderWindow render{};
        sf::Event event{};
        BOOST_CHECK_NO_THROW(scene.draw(render));
        BOOST_CHECK_NO_THROW(scene.handleEvent(event));

        sf::Font font{};
        BOOST_CHECK_NO_THROW(render::PlayerRender::drawPlayer(render,&playerA,0,true,true,font));
    }
}

/* vim: set sw=2 sts=2 et : */
