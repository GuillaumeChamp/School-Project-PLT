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
GameState generateSampleState();
void displayState(const state::GameState& gameState);


int main(int argc, char *argv[]) {

    if (argc >= 2) {
        if (std::strcmp(argv[1], "hello") == 0) {
           std::cout << "hello my dear" << std::endl;
        } 

        else if (std::strcmp(argv[1], "state") == 0) {
           std::cout << "lancement des tests" << std::endl;
           test();
           std::cout << "everything is fine" << std::endl;
        } 

        else if (std::strcmp(argv[1], "render") == 0) {
           
             sf::RenderWindow window(sf::VideoMode(1600, 900), "Citadelles");
            window.setVerticalSyncEnabled(true);

            GameState gamestate=generateSampleState();
            gamestate.setCurrentCharacter(Architect);
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
            GameState gameState=generateSampleState();
            engine::Engine* gameEngine = engine::Engine::getInstance(gameState);

            auto* cmd = new engine::ChooseCharacterCommand(PlayerId::PlayerA,CharacterType::Assassin);
            auto* cmd1(new engine::ChooseCharacterCommand(PlayerId::PlayerB,CharacterType::Thief));
            auto* cmd2(new engine::ChooseCharacterCommand(PlayerId::PlayerC,CharacterType::Magician));
            auto* cmd3(new engine::ChooseCharacterCommand(PlayerId::PlayerD,CharacterType::Warlord));

            gameEngine->addCommand(cmd);
            gameEngine->addCommand(cmd1);
            gameEngine->addCommand(cmd2);
            gameEngine->addCommand(cmd3);

            gameEngine->executeAllCommands();
            displayState(gameState);



        }

        else {
        // error if no argument
        std::cout << "Wrong command. the correct command is  ../bin/client hello" << std::endl;
        }
        return 0;
    }
    return 1;
}

void test(){
    Card card {"card1", CardType::Military, 2};
    Player player {(string &) "player1", PlayerId::PlayerA};
    GameState gameState {std::vector<Player>{player}};
}

void displayState(const state::GameState& gameState) {
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

        std::cout <<"---------------------------------\n Board of "<<player.getNameOfPlayer() << std::endl;
        for (auto& card : player.getBoardOfPlayer()) {
            std::cout << " | Name : " << card.getNameOfCard()
                      << " | Color : " << card.getColorOfCard()
                      << " | Cost : " << card.getCostOfCard()<<"\n---------------------------------"  // Corrected
                      << std::endl;
        }
    }
}


GameState generateSampleState() {
    std::string player1 = "player1";
    std::string player2 = "player2";
    std::string player3 = "player3";
    std::string player4 = "player4";
    Player playerA {player1, PlayerId::PlayerA};
    Player playerB {player2, PlayerId::PlayerB};
    Player playerC {player3 , PlayerId::PlayerC};
    Player playerD {player4, PlayerId::PlayerD};

    Card card1{"1",Commercial,2};
    Card card2{"2",Commercial,2};
    Card card3{"25",Commercial,2};


    playerA.setCharacter(Warlord);
    playerB.setCharacter(Bishop);
    playerC.setCharacter(Merchant);
    playerD.setCharacter(King);

    std::vector<Card> playerABoard{card1};
    std::vector<Card> playerBBoard{card2};
    std::vector<Card> playerCBoard{card2,card1,card3};
    std::vector<Card> playerDBoard{card1,card2};

    playerA.setBoardOfPlayer(playerABoard);
    playerB.setBoardOfPlayer(playerBBoard);
    playerC.setBoardOfPlayer(playerCBoard);
    playerD.setBoardOfPlayer(playerDBoard);

    GameState gameState {std::vector<Player>{playerA,playerB,playerC,playerD}};
    return gameState;
}


