#include "PlayerRender.h"

namespace render {

    std::vector<VisualCard> PlayerRender::drawPlayer(sf::RenderWindow& window, state::Player* playerToRender, int positionId, bool isCrownOwner, bool isRevealed, sf::Font& font) {
        
        std::vector<VisualCard> boardCards;
        std::vector<std::pair<int, int>> coordinatesList = {
            {615,622}, //en bas
            {0,311},  //a gauche
            {615,0}, //en haut
            {1240,311} // a droite
        };

        std::vector<std::pair<int, int>> posCrown = {
            //Coordonné du pixel en haut a gauche du logo couronne de chaqe board
                {985,624}, //en bas
                {370,313},  //a gauche
                {985,2}, //en haut
                {1150,313} // a droite
             };
        
        int boardX = coordinatesList[positionId].first;
        int boardY = coordinatesList[positionId].second;

        int crownX = posCrown[positionId].first;
        int crownY = posCrown[positionId].second;

        //logo couronne
        if (isCrownOwner){
        sf::RectangleShape crown(sf::Vector2f(40,40));
        sf::Texture crownTexture;
        crownTexture.loadFromFile("../res/crown.png");
        crown.setTexture(&crownTexture);

        crown.setPosition(crownX,crownY);

        
        window.draw(crown);
        }

        //Personnage secret si révélé
        if (isRevealed){
            const char* CharacterTypeString[] ={
                    "Assassin",
                    "Thief",
                    "Magician",
                    "King",
                    "Bishop",
                    "Merchant" ,
                    "Architect",
                    "Warlord" ,
                    "NoCharacter"
            };
            std::string characterName = CharacterTypeString[playerToRender->getCharacter()];
            VisualCard character = VisualCard(characterName, crownX, crownY+150);
            character.draw(window);
        }
        if (!isRevealed){
            //Personnage secret
            sf::Texture characterBackgroundTexture;
            characterBackgroundTexture.loadFromFile("../res/dos_rouge.jpg");
            sf::RectangleShape characterBackgroundShape(sf::Vector2f(80,124));
            characterBackgroundShape.setTexture(&characterBackgroundTexture);

            characterBackgroundShape.setPosition(boardX+370, boardY+152);
            window.draw(characterBackgroundShape);
            }
        
        //dessin nombre pièces + nombre cartes
        sf::Text nbOfCoins, nbOfCards;
        nbOfCards.setFillColor(sf::Color::White);
        nbOfCards.setString(std::to_string(playerToRender->getNumberOfCards()));
        nbOfCards.setFont(font);
        nbOfCards.setCharacterSize(35);


        nbOfCoins.setFillColor(sf::Color::White);
        nbOfCoins.setString(std::to_string(playerToRender->getNumberOfCoins()));
        nbOfCoins.setFont(font);
        nbOfCoins.setCharacterSize(35);

        nbOfCards.setPosition(crownX, crownY+50);
        nbOfCoins.setPosition(crownX, crownY+100);
        window.draw(nbOfCards);
        window.draw(nbOfCoins);


        // Ecriture nom joueur
        sf::Text playerName;
        playerName.setFont(font);
        playerName.setFillColor(sf::Color::Red);
        playerName.setString(playerToRender->getNameOfPlayer());
        playerName.setCharacterSize(20);
        playerName.setPosition(boardX-1, boardY-5);

        //Board
        int indexOfCard =0;
        for (auto& card : playerToRender->getBoardOfPlayer()){
                //Creation des cartes des boards
                std::string filename=card.getNameOfCard ();
                VisualCard visualCard(filename, boardX+10 + (indexOfCard % 4) * 90, boardY + 10 + 124 * (indexOfCard / 4));
                visualCard.draw(window);
                boardCards.push_back(visualCard);
                indexOfCard++;
            }

        window.draw(playerName);

        return boardCards;
    }
}
