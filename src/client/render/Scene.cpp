#include "Scene.h"
#include <iostream>  

namespace render {

    Scene::Scene(SceneId sceneId, state::GameState* state) {
        this->sceneId=sceneId;
        this->state=state;
        this->height= 900; 
        this->width=1600;

        listOfButtons.push_back(Button(bank, 700,350));
        listOfButtons.push_back(Button(buttonType::draw, 900,350));
        listOfButtons.push_back(Button(endOfTurn, 780,500));
        listOfButtons.push_back(Button(hand, 1500,850));
        listOfButtons.push_back(Button(help, 1500,50));

        }

    Scene::~Scene() {
    }

    void Scene::draw(sf::RenderWindow& window) {
        // dessine les éléments communs à toutes les scènes

        //Background
        sf::RectangleShape background(sf::Vector2f(width, height));
        background.setFillColor(sf::Color::Black);
        window.draw(background);



        //Affichage des fonds boards + emplacements cartes
        std::vector<std::pair<int, int>> coordinatesList = {
            {615,622}, //en bas
            {0,311},  //a gauche
            {615,0}, //en haut
            {1240,311} // a droite
        };

        for (const auto& coordinates : coordinatesList) {
            //Board background
            sf::RectangleShape board(sf::Vector2f(360, 278));

            float x = static_cast<float>(coordinates.first);
            float y = static_cast<float>(coordinates.second);

            board.setPosition(x, y);
            board.setFillColor(sf::Color::Blue);

            window.draw(board);

            //Cards location
            sf::RectangleShape cardsLocation(sf::Vector2f(80,124));
            cardsLocation.setFillColor(sf::Color::Cyan);
            
            for (int i = 0; i++; i<4){
                for (int j=0; j++; j<2){
                    cardsLocation.setPosition(x+10+90*i, y+10+134*j);
                    window.draw(cardsLocation);
                }
            }

            //Personnage secret
            sf::Texture characterBackgroundTexture;
            characterBackgroundTexture.loadFromFile("../res/dos_rouge.jpg");
            sf::RectangleShape characterBackgroundShape(sf::Vector2f(80,124));
            characterBackgroundShape.setTexture(&characterBackgroundTexture);

            for (int i=0; i++; i<4){
                characterBackgroundShape.setPosition(x+370, y+152);
                window.draw(characterBackgroundShape);
            }
        }

        //logo crown + gold + cartes
        sf::Texture crown, gold, cardLogo;
        crown.loadFromFile("");
        gold.loadFromFile("");
        cardLogo.loadFromFile("");

        sf::Sprite crownSprite(crown);
        sf::Sprite goldSprite(gold);
        sf::Sprite cardLogoSprite(cardLogo);

        std::vector<std::pair<int, int>> posLogo = {
            //Coordonné du pixel en haut a gauche du logo couronne de chaqe board
                {985,624}, //en bas
                {370,313},  //a gauche
                {985,2}, //en haut
                {1150,313} // a droite
             };

        for (const auto& coordinates : posLogo){
            float pos_x = static_cast<float>(coordinates.first);
            float pos_y = static_cast<float>(coordinates.second);
            
            crownSprite.setPosition(pos_x, pos_y);
            goldSprite.setPosition(pos_x+40, pos_y+50);     //Emplacement réfléchis pour garder la place pour le texte
            cardLogoSprite.setPosition(pos_x+40, pos_y+100);

            window.draw(crownSprite);
            window.draw(goldSprite);
            window.draw(cardLogoSprite);
            }
        


        // Affichage des boutons
        for (auto& button : listOfButtons) {
            window.draw(button.getSurface());
        }
        


        //Affichage des cartes des joueurs

        std::vector<state::Player> listOfPlayer = state->getListOfPlayer();
        std::vector<state::Player> listOfPlayerOrder;

        for (auto& player : listOfPlayer) {
            
            if (player.getIdOfPlayer() == sceneId ) {
                //Ordre des joueurs
                int currentIndex;
                for (int i = 0; i < 4; ++i) {
                    if (static_cast<SceneId>(i) == sceneId) {
                        currentIndex= i;
                    }
                }
                listOfPlayerOrder.push_back(player);
                
                for (int i=0; i++; i<3){
                    currentIndex++;
                    currentIndex=currentIndex%4;
                    for (auto& player2 : listOfPlayer){
                        if (player2.getIdOfPlayer()== static_cast<SceneId>(currentIndex)){
                            listOfPlayerOrder.push_back(player2);
                        }
                    }}
            }

        }
        
        

        //Affichage info par joueur
        int i =0;
        for (auto& player : listOfPlayerOrder){
            
            bool isCrownOwner = false;
            bool isRevealed = false;
            if (player.getIdOfPlayer() == state->getCrownOwner()){
                isCrownOwner=true;}
            int indexCurrentCharacter, indexCharacterPlayer;

            for (int k = 0; k < 8; ++k) {
                if (static_cast<state::CharacterType>(k) == player.getCharacter()) {
                    indexCharacterPlayer=k;
                    }
                if (static_cast<state::CharacterType>(k) == state->getCurrentCharacter() ) {
                    indexCurrentCharacter =k;
                    }
                }
            if (indexCharacterPlayer>=indexCurrentCharacter){isRevealed=true;}

            std::vector<render::Card> temp = PlayerRender::drawPlayer(window, &player, i, isCrownOwner, isRevealed);
            displayedCard.insert(std::end(displayedCard), std::begin(temp), std::end(temp));
            i++;
            }
        
        //IDF

         //Hand
        if (IHMState::GetInstance()->isHandDisplayed){
            drawPlayerHand(window);
            }
        //HelpMenu
        if (IHMState::GetInstance()->isHelpDisplayed){
            drawHelp(window);
        }


        for (auto& card : displayedCard){
            window.draw(card.getSurface());
        }

    }


    

    void Scene::handleEvent(sf::Event event) {
        if (event.type == sf::Event::MouseMoved){
            for (auto& cards:displayedCard){
                cards.checkHover(sf::Vector2f(event.mouseMove.x,event.mouseMove.y)); 
            }
            for (auto& button:listOfButtons){
                button.checkHover(sf::Vector2f(event.mouseMove.x,event.mouseMove.y)); 
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            for (auto& cards:displayedCard){
                cards.checkClick(sf::Vector2f(event.mouseButton.x,event.mouseButton.y)); 
            }
            for (auto& button:listOfButtons){
                button.checkClick(sf::Vector2f(event.mouseButton.x,event.mouseButton.y)); 
            }
        }
    }

    void Scene::drawPlayerHand(sf::RenderWindow& window) {

        // fond
        sf::RectangleShape boardBackground(sf::Vector2f(1360, 144));
        boardBackground.setPosition(120,600);
        boardBackground.setFillColor(sf::Color::Blue);
        window.draw(boardBackground);

        std::vector<state::Player> listOfPlayer = state->getListOfPlayer();
        for (auto& player : listOfPlayer) {
            if (player.getIdOfPlayer() == sceneId ) {

        //Creation des cartes de la main du joueur
        int posFirstCardHandX = 130;
        int posFirstCardHandY= 610;
        int i =0;
                for (auto& card : player.getHand()){
                    
                    std::string filename=card.getNameOfCard();
                    displayedCard.push_back(Card(filename,posFirstCardHandX + 90*i, posFirstCardHandY));
                    i++;

                }
    }
    
    }}


    void Scene::drawHelp(sf::RenderWindow& window) {

    sf::RectangleShape helpMenu(sf::Vector2f(900,500));
    helpMenu.setPosition(350, 200);
    helpMenu.setFillColor(sf::Color(200, 200, 200));


    // Texte pour le helpMenu
    sf::Font font;
    font.loadFromFile("../res/Caret-Book.ttf");

    sf::Text helpMenuText;
    helpMenuText.setFont(font);
    helpMenuText.setString("Règles du jeu.\n\n"
                        "Voici les règles du début du jeu\nLigne 2\nLigne 3\nLigne 4\nLigne 5\n"
                        "Ligne 6\nLigne 7\nLigne 8\nLigne 9\nLigne 10\n"
                        "Ligne 11\nLigne 12\nLigne 13\nLigne 14\nLigne 15");
    helpMenuText.setCharacterSize(20);
    helpMenuText.setFillColor(sf::Color::Black);
    helpMenuText.setPosition(370, 220); 

    window.draw(helpMenu);
    window.draw(helpMenuText);
}
}