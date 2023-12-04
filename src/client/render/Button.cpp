#include "Button.h"
#include <iostream>
#include <SFML/Graphics/Texture.hpp>

namespace render {
    Button::Button(ButtonType buttonType, int posX, int posY):InteractiveElement(posX, posY) {
        this->name=buttonType;

        switch (buttonType){
            case bank:
                surface.setPosition(posX,posY);
                surface.setSize(sf::Vector2f(40, 40));
                break;
            case ButtonType::draw:
                surface.setPosition(posX,posY);
                surface.setSize(sf::Vector2f(40, 40));
                break;
            case endOfTurn:
                surface.setPosition(posX,posY);
                surface.setSize(sf::Vector2f(40, 40));
                break;
            case hand:
                surface.setPosition(posX,posY);
                surface.setSize(sf::Vector2f(40, 40));
                break;
            case help:
                surface.setPosition(posX,posY);
                surface.setSize(sf::Vector2f(40, 40));
                break;
        }
    }

    Button::~Button() = default;

    void Button::onHoverEvent() {
        IHMState::getInstance() -> hoverButton = this;
    }

    void Button::onClickEvent() {
        std::string buttonText;
        switch (name) {
            case ButtonType::bank:
                buttonText = "Recevez deux pièces d'or";
                break;
            case ButtonType::draw:
                buttonText = "Piochez une carte parmis 2";
                break;
            case ButtonType::endOfTurn:
                buttonText = "Fin du tour";
                break;
            case ButtonType::hand:
                buttonText = "Ouvre la main du joueur";
                IHMState::getInstance()->isHandDisplayed=!IHMState::getInstance()->isHandDisplayed;
                break;
            case ButtonType::help:
                buttonText = "Ouvre le menu d'aide";
                IHMState::getInstance()->isHelpDisplayed=!IHMState::getInstance()->isHelpDisplayed;
                break;
        }
        std::cout << "Clic sur le bouton : " << buttonText << std::endl;
    }

    void Button::draw(sf::RenderWindow &render) {
        sf::Texture texture;
        switch (this->name){
            case bank:
                texture.loadFromFile("./../res/chest.png");
                break;
            case ButtonType::draw:
                texture.loadFromFile("./../res/dos_rouge.jpg");
                break;
            case endOfTurn:
                texture.loadFromFile("./../res/dos_vert.jpg");
                break;
            case hand:
                texture.loadFromFile("./../res/dos_vert.jpg");
                break;
            case help:
                texture.loadFromFile("./../res/help.png");
                break;
        }
        surface.setTexture(&texture);
        render.draw(surface);
    }

}
