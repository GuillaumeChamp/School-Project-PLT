#include "Scene.h"
#include <iostream>
#include "config.h"
#include <fstream>
#include <utility>

#define PATH "/tmp/cit_ihm.txt"

using namespace render;

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

Scene::Scene(SceneId sceneId, std::shared_ptr<state::GameState> state,bool & notifier) : notifier(notifier) {
    std::string res = RES_DIR;
    this->isPlayingScene = false;
    this->sceneId = sceneId;
    this->state = std::move(state);
    this->height = 900;
    this->width = 1600;
    this->fontText.loadFromFile(res + "Garet-Book.ttf");
    this->fontTitle.loadFromFile(res + "OldLondon.ttf");

    listOfButtons.emplace_back(ButtonType::bank, 700, 350);
    listOfButtons.emplace_back(ButtonType::draw, 900, 350);
    listOfButtons.emplace_back(ButtonType::endOfTurn, 780, 500);
    listOfButtons.emplace_back(ButtonType::hand, 1450, 800);
    listOfButtons.emplace_back(ButtonType::help, 1500, 50);

    //Background
    this->background = sf::RectangleShape();
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color(21, 25, 29));

    //logo crown + gold + cartes
    sf::Texture crown, gold, card;
    crown.loadFromFile(res + "noCrown.png");
    gold.loadFromFile(res + "coin.png");
    card.loadFromFile(res + "coin.png");
    this->crownTexture = crown;
    this->goldTexture = gold;
    this->cardTexture = card;

    // Fill help menu
    this->helpMenuText = sf::Text();
    helpMenuText.setFont(fontText);
    helpMenuText.setString("Regles du jeu.\n\n"
                           "Voici les regles de Citadelles\nLigne 2\nLigne 3\nLigne 4\nLigne 5\n"
                           "Ligne 6\nLigne 7\nLigne 8\nLigne 9\nLigne 10\n"
                           "Ligne 11\nLigne 12\nLigne 13\nLigne 14\nLigne 15");
    helpMenuText.setCharacterSize(20);
    helpMenuText.setFillColor(sf::Color(55, 53, 53));
    helpMenuText.setPosition(370, 220);
}

Scene::~Scene() {
    this->listOfButtons.clear();
    this->displayedCard.clear();
}

void Scene::draw(sf::RenderWindow &window) {
    displayedCard.clear();

    // is the owner of the scene currently playing
    isPlayingScene = (static_cast<int>(state->getPlaying()) == static_cast<int>(sceneId));

    // Background
    window.draw(background);

    // Draw board background and card display
    std::vector<std::pair<float, float>> coordinatesList = {
            {615,  622}, //en bas
            {0,    311},  //a gauche
            {615,  0}, //en haut
            {1240, 311} // a droite
    };

    for (const auto &coordinates: coordinatesList) {
        //Board background
        sf::RectangleShape board(sf::Vector2f(360, 278));

        float x = coordinates.first;
        float y = coordinates.second;

        board.setPosition(x, y);
        board.setFillColor(sf::Color(165, 134, 105));

        window.draw(board);

        //Cards location
        sf::RectangleShape cardsLocation(sf::Vector2f(80, 124));
        cardsLocation.setFillColor(sf::Color(233, 220, 205));

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2; j++) {
                cardsLocation.setPosition(x + 10 + 90 * (float) i, y + 10 + 134 * (float) j);
                window.draw(cardsLocation);
            }
        }

    }

    std::vector<std::pair<float, float>> posLogo = {
            //Coordonné du pixel en haut a gauche du logo couronne de chaqe board
            {985,  624}, //en bas
            {370,  313},  //a gauche
            {985,  2}, //en haut
            {1150, 313} // a droite
    };

    for (const auto &coordinates: posLogo) {
        float pos_x = coordinates.first;
        float pos_y = coordinates.second;

        sf::RectangleShape crownIcon, goldIcon, cardIcon;
        crownIcon.setSize(sf::Vector2f(40, 40));
        goldIcon.setSize(sf::Vector2f(40, 40));
        cardIcon.setSize(sf::Vector2f(40, 40));

        crownIcon.setPosition(pos_x, pos_y);
        crownIcon.setTexture(&crownTexture);
        goldIcon.setPosition(pos_x + 40, pos_y + 50);     //Emplacement réfléchis pour garder la place pour le texte
        goldIcon.setTexture(&goldTexture);
        cardIcon.setPosition(pos_x + 40, pos_y + 100);
        cardIcon.setTexture(&cardTexture);

        window.draw(crownIcon);
        window.draw(goldIcon);
        window.draw(cardIcon);
    }

    //Affichage des cartes des joueurs
    std::vector<state::Player> listOfPlayer = state->getListOfPlayer();
    std::vector<state::Player> listOfPlayerOrder;

    int idOfSceneOwner = sceneId;
    listOfPlayerOrder.push_back(listOfPlayer[sceneId - 1]);

    for (int i = 0; i < 3; i++) {
        idOfSceneOwner++;
        idOfSceneOwner = idOfSceneOwner > 4 ? 1 : idOfSceneOwner;
        for (auto &player2: listOfPlayer) {
            if (player2.getIdOfPlayer() == idOfSceneOwner) {
                listOfPlayerOrder.push_back(player2);
                break;
            }
        }
    }

    //Affichage info par joueur
    int i = 0;
    int indexCurrentCharacter, indexCharacterPlayer;
    for (auto &player: listOfPlayerOrder) {
        bool isCrownOwner = false;
        bool isRevealed = false;
        if (player.getIdOfPlayer() == state->getCrownOwner()) {
            isCrownOwner = true;
        }
        indexCharacterPlayer = player.getCharacter();
        indexCurrentCharacter = state->getCurrentCharacter();
        if (indexCharacterPlayer <= indexCurrentCharacter) {
            isRevealed = true;
        }

        std::vector<VisualCard> temp = PlayerRender::drawPlayer(window, &player, i, isCrownOwner, isRevealed,
                                                                fontTitle);
        displayedCard.insert(std::end(displayedCard), std::begin(temp), std::end(temp));
        i++;
    }

    //Capacity button
    state::Player currentPlayer = listOfPlayerOrder[0];
    bool found = false;

    for (const auto &button: listOfButtons) {
        if (button.getType() == capacity) {
            found = true;
        }
    }

    if (currentPlayer.isCapacityAvailable() && !found) {
        listOfButtons.emplace_back(ButtonType::capacity, 1500, 700);
    }

    if (!currentPlayer.isCapacityAvailable() && found) {
        for (auto it = listOfButtons.begin(); it != listOfButtons.end();) {
            if (it->getType() == capacity) {
                it = listOfButtons.erase(it);
            } else {
                ++it;
            }
        }
    }
    // Affichage des boutons
    for (auto &button: listOfButtons) {
        button.draw(window);
    }

    //IDF
    std::string currentCharacterName = CharacterTypeString[state->getCurrentCharacter()];
    VisualCard currentCharacterCard = VisualCard(currentCharacterName, 10, 10);
    currentCharacterCard.draw(window);

    sf::Text IDFText;
    IDFText.setFont(fontTitle);
    IDFText.setString(std::to_string(indexCurrentCharacter) + " / 8");
    IDFText.setCharacterSize(20);
    IDFText.setFillColor(sf::Color::White);
    IDFText.setPosition(33, 140);
    window.draw(IDFText);

    //Hand
    if (IHMState::getInstance()->isHandDisplayed) {
        drawPlayerHand(window);
    }
    //HelpMenu
    if (IHMState::getInstance()->isHelpDisplayed) {
        drawHelp(window);
    }

    //Show character to pick if game ask to pick
    if (state->getGamePhase() == 0 && isPlayingScene) {
        promptCharacterSelection(true, window);
    }

    //Show card to pick if game ask to pick
    if (state->getSubPhase() == 1 && isPlayingScene) {
        DisplayDrawableCard(window);
    }

    //Pre Capacity
    if (state->getSubPhase() == 2 && isPlayingScene) {

        if (currentPlayer.getCharacter() == 0 ||
            currentPlayer.getCharacter() == 1) { //Si le choix de la cible est un personnage (Assassin, Voleur)
            promptCharacterSelection(false, window);
        }

        if (currentPlayer.getCharacter() == 2) { //Si le choix de la cible est un joueur (Magicien)
            //On affiche un message pour demander au joueur de cliquer sur le board du joueur qu'il souhaite cibler
            sf::Text magicianMessage;
            magicianMessage.setFont(fontTitle);
            magicianMessage.setFillColor(sf::Color::White);
            magicianMessage.setOutlineThickness(2.0f);
            magicianMessage.setOutlineColor(sf::Color::Black);
            magicianMessage.setString("Veuillez choisir un joueur adverse");
            magicianMessage.setCharacterSize(25);
            magicianMessage.setPosition((1600 - magicianMessage.getLocalBounds().width) / 2,
                                        (900 - magicianMessage.getLocalBounds().height) / 2);
            window.draw(magicianMessage);
        }
    }

    //Draft, choix du personnage à bannir
    if (state->getSubPhase() == 3 && isPlayingScene ) {
        promptCharacterSelection(true, window);
    }

    // Card Zoom
    VisualCard *cardToZoom = (IHMState::getInstance()->hoverCard);
    if (cardToZoom != nullptr) {
        (*cardToZoom).zoomCard();
        (*cardToZoom).draw(window);
    }
}


void Scene::handleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseMoved) {
        IHMState::getInstance()->hoverCard = nullptr;
        for (auto &cards: displayedCard) {
            if (cards.checkHover((float) event.mouseMove.x, (float) event.mouseMove.y)) {
                cards.onHoverEvent();
                break;
            }
        }
        IHMState::getInstance()->hoverButton = nullptr;
        for (auto &button: listOfButtons) {
            if (button.checkHover((float) event.mouseMove.x, (float) event.mouseMove.y)) {
                button.onHoverEvent();
                break;
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        //Get the board owner of the click region
        sf::Vector2i boardsPos[4] = {
                {615,  622}, // en bas
                {0,    311},   // à gauche
                {615,  0},   // en haut
                {1240, 311} // à droite
        };
        int target = this->sceneId;
        for (int i = 0; i < 4; ++i) {
            if (event.mouseButton.x >= boardsPos[i].x &&
                event.mouseButton.y >= boardsPos[i].y &&
                event.mouseButton.x < boardsPos[i].x + 360 &&
                event.mouseButton.y < boardsPos[i].y + 278) {
                // Le clic est dans la zone i
                target = target + i;
                if (target>4){
                    target= target-4;
                }
                break;
            }
        }
        //Capacity
        if (state->getSubPhase() == 2) {
            if (state->getCurrentCharacter() == 2) { //Si le choix de la cible est un joueur (Magicien)
                auto commandContent = std::to_string(target);
                sendData(commandContent);
                for (int i = 0; i < 4; ++i) {
                    if (event.mouseButton.x >= boardsPos[i].x &&
                        event.mouseButton.y >= boardsPos[i].y &&
                        event.mouseButton.x < boardsPos[i].x + 360 &&
                        event.mouseButton.y < boardsPos[i].y + 278) {
                        // Le clic est dans la zone i
                        std::cout << "Capacité effectuée sur le joueur " << i + 1 << std::endl;
                        return;
                    }
                }
            }
        }
        for (auto &button: listOfButtons) {
            if (button.checkClick((float) event.mouseButton.x, (float) event.mouseButton.y)) {
                std::string payload = button.onClickEvent();
                if (payload.empty()){
                    return;
                }
                payload.append(",").append(std::to_string(target));
                sendData(payload);
                return;
            }
        }
        for (auto &cards: displayedCard) {
            if (cards.checkClick((float) event.mouseButton.x, (float) event.mouseButton.y)) {
                // Pour les capacités qui ciblent des personnages ou batiments, les cibles disponibles sont des cards donc la cible est renvoyée normalement, et est ignorée par l'engine si elle n'est pas valable
                // Pour la Draft de même, un personnages disponible pour etre choisi ou banni est une cards
                std::string cardName = cards.onClickEvent();
                std::string payload = cardName +","+ std::to_string(target);
                for (int i=0;i< 9;i++){
                    if (cardName==CharacterTypeString[i]){
                        payload = "3,"+std::to_string(sceneId)+','+std::to_string(i);
                        break;
                    }
                }
                sendData(payload);
                return;
            }
        }
    }
}

void Scene::drawPlayerHand(sf::RenderWindow &window) {
    // fond
    sf::RectangleShape boardBackground(sf::Vector2f(1360, 144));
    boardBackground.setPosition(120, 600);
    boardBackground.setFillColor(sf::Color(76, 68, 53));
    window.draw(boardBackground);

    std::vector<state::Player> listOfPlayer = state->getListOfPlayer();
    for (auto &player: listOfPlayer) {
        if ((int) player.getIdOfPlayer() == sceneId) {
            //Creation des cartes de la main du joueur
            int posFirstCardHandX = 130;
            int posFirstCardHandY = 610;
            int i = 0;
            for (auto &card: player.getHand()) {
                std::string filename = card.getNameOfCard();
                displayedCard.emplace_back(filename, posFirstCardHandX + 90 * i, posFirstCardHandY);
                i++;
            }
        }
    }
}

void Scene::drawHelp(sf::RenderWindow &window) {
    sf::RectangleShape helpMenu(sf::Vector2f(900, 500));
    helpMenu.setPosition(350, 200);
    helpMenu.setFillColor(sf::Color(238, 225, 208));
    helpMenu.setOutlineThickness(3.0f);
    helpMenu.setOutlineColor(sf::Color::Black);
    window.draw(helpMenu);
    window.draw(helpMenuText);
}

void Scene::promptCharacterSelection(bool isPartial, sf::RenderWindow &window) {
    std::vector<state::CharacterType> availableCharacter;

    int indexFirstCharacterX = 445;
    int indexFirstCharacterY = 388;

    sf::RectangleShape characterChoiceBackground;
    characterChoiceBackground.setPosition(443,386);

    if (isPartial) {
        availableCharacter = state->getAvailableCharacter();
        indexFirstCharacterX += (8 - (int) availableCharacter.size()) / 2 * 90;
        characterChoiceBackground.setSize(sf::Vector2f(90 * (float) availableCharacter.size() + 10, 134));
    } else {
        characterChoiceBackground.setSize(sf::Vector2f(730, 134));
        availableCharacter = {state::ASSASSIN,state::THIEF,state::MAGICIAN,state::KING,state::BISHOP,state::MERCHANT,state::ARCHITECT,state::WARLORD};
    }

    characterChoiceBackground.setFillColor(sf::Color(76, 68, 53));
    window.draw(characterChoiceBackground);

    for (size_t i = 0; i < availableCharacter.size(); i++) {
        int character = availableCharacter[i];
        std::string characterName = CharacterTypeString[character];

        VisualCard characterCard = VisualCard(characterName,
                                              (float) indexFirstCharacterX + 90 * (float) i,
                                              (float) indexFirstCharacterY);
        characterCard.draw(window);
        displayedCard.push_back(characterCard);
    }
}

void Scene::DisplayDrawableCard(sf::RenderWindow &window) {
    std::vector<state::Card> drawableCards = state->getDrawableCards();

    sf::RectangleShape background = sf::RectangleShape(
            sf::Vector2f(90 * (float) drawableCards.size() + 10, 134));
    background.setPosition(755, 386);
    background.setFillColor(sf::Color(76, 68, 53));
    window.draw(background);
    int i = 0;
    for (auto &card: drawableCards) {
        std::string cardName = card.Card::getNameOfCard();
        VisualCard drawableCard = VisualCard(cardName, 760 + 90 * (float) i, 388);
        i++;
        drawableCard.draw(window);
        displayedCard.push_back(drawableCard);
    }
}

void Scene::sendData (std::string& content) {
    this->notifier= true;
    std::ofstream MyFile(PATH);
    MyFile << content;
}