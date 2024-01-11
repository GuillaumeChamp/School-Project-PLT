#include <iostream>
#include <cstring>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include "render.h"
#include "engine.h"
#include "thread"

using namespace std;
using namespace state;
using namespace engine;

void test();

void generateSampleState(state::GameState &gameStateSample);

void generateAndStartWindow();

void commandGenerator(state::GameState &gameState);

int main(int argc, char *argv[]) {

    if (argc >= 2) {
        if (std::strcmp(argv[1], "hello") == 0) {
            std::cout << "hello my dear" << std::endl;
        } else if (std::strcmp(argv[1], "state") == 0) {
            std::cout << "lancement des tests" << std::endl;
            std::cout << "everything is fine" << std::endl;
        } else if (std::strcmp(argv[1], "render") == 0) {
            generateAndStartWindow();
        } else if (std::strcmp(argv[1], "engine") == 0) {
            state::GameState gameState("Simon", "Karl", "Nordine", "Guillaume");
            sf::RenderWindow window(sf::VideoMode(1600, 900), "Citadelles");
            window.setVerticalSyncEnabled(true);
            render::Scene sceneA(render::SceneId::PlayerB, &gameState);
            //Engine::getInstance(gameState).startThread();
            std::thread thread1([&gameState]() {
                commandGenerator(gameState);
            });
            while (window.isOpen()) {
                sf::Event event{};
                while (window.pollEvent(event)) {
                    sceneA.handleEvent(event);
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                }
                window.clear();

                sceneA.draw(window);
                window.display();
            }
        } else {
            // error if no argument
            std::cout << "Wrong command. the correct command is  ../bin/client X" << std::endl;
        }
        return 0;
    }
    return 1;
}

void generateSampleState(state::GameState &gameStateSample) {

    Card card1{"1", CardType::COMMERCIAL, 2};
    Card card2{"2", CardType::COMMERCIAL, 2};
    Card card3{"25", CardType::COMMERCIAL, 2};

    Player playerA = gameStateSample.getPlayer(PlayerId::PLAYER_A);
    Player playerB = gameStateSample.getPlayer(PlayerId::PLAYER_B);
    Player playerC = gameStateSample.getPlayer(PlayerId::PLAYER_C);
    Player playerD = gameStateSample.getPlayer(PlayerId::PLAYER_D);

    playerA.setCharacter(CharacterType::KING);
    playerA.setCapacityAvailability(true);
    playerB.setCharacter(CharacterType::WARLORD);
    playerC.setCharacter(CharacterType::BISHOP);
    playerD.setCharacter(CharacterType::ASSASSIN);

    std::vector<Card> playerABoard{card1};
    std::vector<Card> playerBBoard{card2};
    std::vector<Card> playerCBoard{card2, card1, card3};
    std::vector<Card> playerDBoard{card1, card2};

    playerA.setBoardOfPlayer(playerABoard);
    playerB.setBoardOfPlayer(playerBBoard);
    playerC.setBoardOfPlayer(playerCBoard);
    playerD.setBoardOfPlayer(playerDBoard);

    gameStateSample.updatePlayer(playerA);
    gameStateSample.updatePlayer(playerB);
    gameStateSample.updatePlayer(playerC);
    gameStateSample.updatePlayer(playerD);

    gameStateSample.setCurrentCharacter(KING);
    gameStateSample.setGamePhase(CALL_CHARACTER);
    gameStateSample.setSubPhase(Default);
    gameStateSample.setPlaying(PLAYER_A);
    gameStateSample.setCrownOwner(PLAYER_B);
}

void generateAndStartWindow() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Citadelles");
    window.setVerticalSyncEnabled(true);
    state::GameState gamestate("Simon", "Karl", "Nordine", "Guillaume");

    generateSampleState(gamestate);
    render::Scene sceneA(render::SceneId::PlayerB, &gamestate);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            sceneA.handleEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();

        sceneA.draw(window);
        window.display();
    }
}

void commandGenerator(state::GameState &state) {
    Engine::getInstance(state).startThread();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Engine::getInstance(state).addCommand(new StartGameCommand(PLAYER_A));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Engine::getInstance(state).addCommand(new ChooseCharacterCommand(PLAYER_A, KING));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Engine::getInstance(state).addCommand(new ChooseCharacterCommand(PLAYER_B, THIEF));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Engine::getInstance(state).addCommand(new ChooseCharacterCommand(PLAYER_C, MAGICIAN));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Engine::getInstance(state).addCommand(new ChooseCharacterCommand(PLAYER_D, BISHOP));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Engine::getInstance(state).addCommand(new DrawCommand(PLAYER_B));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Engine::getInstance(state).addCommand(new ChooseCardCommand(PLAYER_B, state.getDrawableCards().front()));
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout<<state.getPlayer(state::PLAYER_B).getHand().size()<<endl;
    state::Player plr1 = state.getPlayer(state::PLAYER_B);
    plr1.setNumberOfCoins(10);
    state.updatePlayer(plr1);
    Engine::getInstance(state).addCommand(new ChooseCardCommand(PLAYER_B, state.getPlayer(PLAYER_B).getHand().front()));
    std::this_thread::sleep_for(std::chrono::seconds(2));
    Engine::getInstance(state).addCommand(new UseCharacterAbilityCommand(PLAYER_B, NO_PLAYER, KING));
    std::this_thread::sleep_for(std::chrono::seconds(2));
    Engine::getInstance(state).addCommand(new EndOfTurnCommand(PLAYER_B));
    std::this_thread::sleep_for(std::chrono::seconds(2));
    Engine::getInstance(state).addCommand(new DrawCommand(PLAYER_C));
    std::this_thread::sleep_for(std::chrono::seconds(1));


    terminate();
}




