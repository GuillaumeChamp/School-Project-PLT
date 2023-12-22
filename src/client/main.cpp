#include <iostream>
#include <cstring>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <state.h>
#include "render.h"
#include "engine.h"

using namespace std;
using namespace state;

void test();
void generateSampleState(state::GameState& gameStateSample);
void displayState(const state::GameState& gameState);


int main(int argc, char *argv[]) {

    if (argc >= 2) {
        if (std::strcmp(argv[1], "hello") == 0) {
           std::cout << "hello my dear" << std::endl;
        } 

        else if (std::strcmp(argv[1], "state") == 0) {
           std::cout << "lancement des tests" << std::endl;
           std::cout << "everything is fine" << std::endl;
        } 

        else if (std::strcmp(argv[1], "render") == 0) {
           
             sf::RenderWindow window(sf::VideoMode(1600, 900), "Citadelles");
            window.setVerticalSyncEnabled(true);
            state::GameState gamestate("Simon","Karl","Nordine","Guillaume"); 

            generateSampleState(gamestate);
            gamestate.setCurrentCharacter(ARCHITECT);
            render::Scene sceneA(render::SceneId::PlayerA, &gamestate);
        

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

        
        else if (std::strcmp(argv[1], "engine") == 0) {

            state::GameState gameState("Simon","Karl","Nordine","Guillaume"); 

            engine::Engine* gameEngine = engine::Engine::getInstance(gameState);

            auto* startGameCmd = new engine::StartGameCommand(gameState.getPlaying());
            gameEngine->addCommand(startGameCmd);
            gameEngine->executeAllCommands();

            generateSampleState(gameState);

            
             
            //auto* cmd1 = new engine::ChooseCharacterCommand(gameState.getPlaying(),CharacterType::ASSASSIN);
            //gameEngine->addCommand(cmd1);
            
            
            displayState(gameState);


        }

        else {
        // error if no argument
        std::cout << "Wrong command. the correct command is  ../bin/client X" << std::endl;
        }
        return 0;
    }
    return 1;
}

 

void displayState(const state::GameState& gameState) {
    std::cout << "---------------------------------\n | Phase : " << gameState.getGamePhase()<<"\n---------------------------------"<< std::endl;
    std::cout << "---------------------------------\n | Avaible Characters : " <<std::endl;
    for (auto& character : gameState.getAvailableCharacter()) {
        std::cout << " | Character : " << character;
    }std::cout<<"\n"<<std::endl;
    for (auto& player : gameState.getListOfPlayer()) {
        std::cout << " | Name: " << player.getNameOfPlayer()
                  << " | Character: " << player.getCharacter()
                  << " | Nb of cards: " << player.getNumberOfCards()
                  << " | Nb of coins: " << player.getNumberOfCoins()
                  << std::endl;

        std::cout <<"---------------------------------\n Hand of "<<player.getNameOfPlayer() << std::endl;
        for (auto& card : player.getHand()) {
            std::cout << " | Name : " << card.getNameOfCard()
                      << " | Color : " << card.getColorOfCard()
                      << " | Cost : " << card.getCostOfCard()<<"\n---------------------------------"
                      << std::endl;
        }

        std::cout <<"---------------------------------\n Board of "<<player.getNameOfPlayer() << " Size : " <<player.getBoardOfPlayer().size() << std::endl;
        
        for (auto& card : player.getBoardOfPlayer()) {
            std::cout << " | Name : " << card.getNameOfCard()
                      << " | Color : " << card.getColorOfCard()
                      << " | Cost : " << card.getCostOfCard()<<"\n---------------------------------"  // Corrected
                      << std::endl;
        }
    }
}


void generateSampleState(state::GameState& gameStateSample) {
    
    Card card1{"1",CardType::COMMERCIAL,2};
    Card card2{"2",CardType::COMMERCIAL,2};
    Card card3{"25",CardType::COMMERCIAL,2};

    Player playerA=gameStateSample.getPlayer(PlayerId::PLAYER_A);
    Player playerB=gameStateSample.getPlayer(PlayerId::PLAYER_B);
    Player playerC=gameStateSample.getPlayer(PlayerId::PLAYER_C);
    Player playerD=gameStateSample.getPlayer(PlayerId::PLAYER_D);

    playerA.setCharacter(CharacterType::NO_CHARACTER);
    playerB.setCharacter(CharacterType::NO_CHARACTER);
    playerC.setCharacter(CharacterType::NO_CHARACTER);
    playerD.setCharacter(CharacterType::NO_CHARACTER);

    std::vector<Card> playerABoard{card1};
    std::vector<Card> playerBBoard{card2};
    std::vector<Card> playerCBoard{card2,card1,card3};
    std::vector<Card> playerDBoard{card1,card2};

    playerA.setBoardOfPlayer(playerABoard);
    playerB.setBoardOfPlayer(playerBBoard);
    playerC.setBoardOfPlayer(playerCBoard);
    playerD.setBoardOfPlayer(playerDBoard);

    gameStateSample.updatePlayer(playerA);
    gameStateSample.updatePlayer(playerB);
    gameStateSample.updatePlayer(playerC);
    gameStateSample.updatePlayer(playerD);
    
}




