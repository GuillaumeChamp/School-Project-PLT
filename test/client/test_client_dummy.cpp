
#include <boost/test/unit_test.hpp>
#include "render.h"

#include <SFML/Graphics.hpp>
#include <sys/stat.h>

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

        std::string player1= "player1";
        std::string player2= "player2";
        std::string player3= "player3";
        std::string player4= "player4";

        state::Player playerA {player1, state::PlayerId::PlayerA};
        state::Player playerB {player2, state::PlayerId::PlayerB};
        state::Player playerC {player3, state::PlayerId::PlayerC};
        state::Player playerD {player4, state::PlayerId::PlayerD};

        state::GameState gameState {std::vector<state::Player>{playerA,playerB,playerC,playerD}};
        render::Scene scene{render::SceneId::PlayerA,&gameState};

        sf::RenderWindow render{};
        sf::Event event{};
        BOOST_CHECK_NO_THROW(scene.draw(render));
        BOOST_CHECK_NO_THROW(scene.handleEvent(event));

        sf::Font font{};
        BOOST_CHECK_NO_THROW(render::PlayerRender::drawPlayer(render,&playerA,0,true,true,font));

        //Is file reachable
        const char* dir = "./res/Garet-Book.ttf";
        struct stat sb{};
        BOOST_CHECK_EQUAL(stat(dir, &sb), 0);

    }
}

/* vim: set sw=2 sts=2 et : */
