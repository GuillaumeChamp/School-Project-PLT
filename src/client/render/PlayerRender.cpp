#include "PlayerRender.h"

namespace render {

    void PlayerRender::drawPlayer(sf::RenderWindow& render, state::Player* playerToRender, int positionId, bool isCrownOwner, bool isRevealed) {
        
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
        
        float boardX = static_cast<float>(coordinatesList[positionId].first);
        float boardY = static_cast<float>(coordinatesList[positionId].second);

        float crownX = static_cast<float>(posCrown[positionId].first);
        float crownY = static_cast<float>(posCrown[positionId].second);

        sf::Font fontTitre, fontText;
        fontTitre.loadFromFile("../res/OldLondon.ttf");

        fontText.loadFromFile("../res/Caret-Book.ttf");

        //logo couronne
        if (isCrownOwner){
        sf::Texture crown;
        crown.loadFromFile("");
        sf::Sprite crownSprite(crown);
        crownSprite.setPosition(crownX,crownY);
        
        render.draw(crownSprite);
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
    "NoCharacter" };
            std::string characterName = CharacterTypeString[playerToRender->getCharacter()];
            Card character = Card(characterName, crownX, crownY+150);
            render.draw(character);
        }
        
        //dessin nombre pièces + nombre cartes
        sf::Text nbOfCoins, nbOfCards;
        nbOfCards.setString(std::to_string(playerToRender->getNumberOfCards()));
        nbOfCoins.setString(std::to_string(playerToRender->getNumberOfCoins()));
        nbOfCoins.setFont(fontTitre);
        nbOfCards.setFont(fontTitre);
        nbOfCards.setCharacterSize(20);
        nbOfCoins.setCharacterSize(20);
        nbOfCards.setPosition(crownX, crownY+50);
        nbOfCoins.setPosition(crownX, crownY+100);
        nbOfCards.setFillColor(sf::Color::White);
        nbOfCoins.setFillColor(sf::Color::White);
        render.draw(nbOfCards);
        render.draw(nbOfCoins);


        // Ecriture nom joueur
        sf::Text playerName;
        playerName.setFont(fontTitre);
        playerName.setString(playerToRender->getNameOfPlayer());
        playerName.setCharacterSize(20);
        playerName.setPosition(boardX+1, boardY+1);
        playerName.setFillColor(sf::Color::White);
        render.draw(playerName);

    }

} 
