#include "PlayerRender.h"
#include "config.h"


using namespace render;

std::vector<VisualCard> PlayerRender::drawPlayer(sf::RenderWindow &window, state::Player *playerToRender,
                                                 int positionId, bool isCrownOwner,bool isRevealed, sf::Font &font) {

    std::vector<VisualCard> boardCards;
    std::vector<std::pair<float, float>> coordinatesList = {
            {615,  622}, //en bas
            {0,    311},  //a gauche
            {615,  0}, //en haut
            {1240, 311} // a droite
    };

    std::vector<std::pair<float, float>> posCrown = {
            //Coordonné du pixel en haut a gauche du logo couronne de chaqe board
            {985,  624}, //en bas
            {370,  313},  //a gauche
            {985,  2}, //en haut
            {1150, 313} // a droite
    };

    float boardX = coordinatesList[positionId].first;
    float boardY = coordinatesList[positionId].second;

    float offBoardOffsetX = posCrown[positionId].first;
    float offBoardOffsetY = posCrown[positionId].second;

    //logo couronne
    if (isCrownOwner) {
        sf::RectangleShape crown(sf::Vector2f(40, 40));
        sf::Texture crownTexture;

        std::string res = RES_DIR;
        crownTexture.loadFromFile(res.append("crown.png"));
        crown.setTexture(&crownTexture);

        crown.setPosition(offBoardOffsetX, offBoardOffsetY);
        window.draw(crown);
    }

    // Show character if revealed
    if (isRevealed) {
        const char *CharacterTypeString[] = {
                "NoCharacter",
                "Assassin",
                "Thief",
                "Magician",
                "King",
                "Bishop",
                "Merchant",
                "Architect",
                "Warlord",
        };
        std::string characterName = CharacterTypeString[playerToRender->getCharacter()];
        VisualCard character = VisualCard(characterName, offBoardOffsetX, offBoardOffsetY + 150);
        character.draw(window);
    } else {
        //Personnage secret
        sf::Texture characterBackgroundTexture;
        std::string res = RES_DIR;
        characterBackgroundTexture.loadFromFile(res + "NoCharacter.png");
        sf::RectangleShape characterBackgroundShape(sf::Vector2f(80, 124));
        characterBackgroundShape.setTexture(&characterBackgroundTexture);

        characterBackgroundShape.setPosition(boardX + 370, boardY + 152);
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

    nbOfCards.setPosition(offBoardOffsetX, offBoardOffsetY + 50);
    nbOfCoins.setPosition(offBoardOffsetX, offBoardOffsetY + 100);
    window.draw(nbOfCards);
    window.draw(nbOfCoins);


    // Ecriture nom joueur
    sf::Text playerName;
    playerName.setFont(font);
    playerName.setFillColor(sf::Color::White);
    playerName.setOutlineThickness(2.0f);
    playerName.setOutlineColor(sf::Color::Black);
    playerName.setString(playerToRender->getNameOfPlayer());
    playerName.setCharacterSize(16);
    playerName.setPosition(boardX, boardY);

    //Board
    int indexOfCard = 0;
    for (auto &card: playerToRender->getBoardOfPlayer()) {
        //Creation des cartes des boards
        std::string filename = card.getNameOfCard();
        VisualCard visualCard(filename, boardX + 10 + (float) (indexOfCard % 4) * 90,
                              boardY + 10 + (float) 124 * (indexOfCard / 4));
        visualCard.draw(window);
        boardCards.push_back(visualCard);
        indexOfCard++;
    }

    window.draw(playerName);

    return boardCards;
}
