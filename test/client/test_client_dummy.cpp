
#include <boost/test/unit_test.hpp>
#include "render.h"

#include <SFML/Graphics.hpp>
#include <sys/stat.h>
#include "config.h"

BOOST_AUTO_TEST_CASE(TestSFML)
{

    ::sf::Texture texture;
    BOOST_CHECK(texture.getSize() == ::sf::Vector2<unsigned int>{});

    render::Button button{render::ButtonType::hand, 10, 20};
    BOOST_CHECK_EQUAL(button.getType(), render::ButtonType::hand);
    BOOST_CHECK_EQUAL(button.getSurface().getPosition().x, 10);
    BOOST_CHECK_EQUAL(button.getSurface().getPosition().y, 20);

    BOOST_CHECK_EQUAL(render::IHMState::getInstance()->hoverCard, nullptr);
    BOOST_CHECK_EQUAL(render::IHMState::getInstance()->hoverButton, nullptr);
    BOOST_CHECK_EQUAL(render::IHMState::getInstance()->isHandDisplayed, false);
    BOOST_CHECK_EQUAL(render::IHMState::getInstance()->isHelpDisplayed, false);

    std::string player1 = "player1";
    std::string player2 = "player2";
    std::string player3 = "player3";
    std::string player4 = "player4";

    state::Player playerA{player1, state::PlayerId::PLAYER_A};
    state::Player playerB{player2, state::PlayerId::PLAYER_B};
    state::Player playerC{player3, state::PlayerId::PLAYER_C};
    state::Player playerD{player4, state::PlayerId::PLAYER_D};

    std::shared_ptr<state::GameState> gameState= std::make_shared<state::GameState>(player1, player2, player3, player4);
    gameState->updatePlayer(playerA);
    gameState->updatePlayer(playerB);
    gameState->updatePlayer(playerC);
    gameState->updatePlayer(playerD);
    bool notif = false;
    render::Scene scene{render::SceneId::PlayerA, gameState,notif};

    sf::RenderWindow render{};
    sf::Event event{};
    BOOST_CHECK_NO_THROW(scene.draw(render));
    BOOST_CHECK_NO_THROW(scene.handleEvent(event));

    sf::Font font{};
    BOOST_CHECK_NO_THROW(render::PlayerRender::drawPlayer(render, &playerA, 0, true, true, font));

    //Is file reachable
    std::string path = RES_DIR;
    path.append("Garet-Book.ttf");
    struct stat sb{};
    BOOST_CHECK_EQUAL(stat(path.c_str(), &sb), 0);


}

/* vim: set sw=2 sts=2 et : */
