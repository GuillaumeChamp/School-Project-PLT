#include "Button.h"
#include <iostream>
#include <SFML/Graphics/Texture.hpp>

namespace render {
    Button::Button(ButtonType buttonType, int posX, int posY):InteractiveElement(posX, posY) {
        sf::Texture  texture1, texture2, texture3, texture4, texture5;
        this->name=buttonType;

        switch (buttonType){
            case bank:
                surface.setPosition(posX,posY);
                texture1.loadFromFile("./res/chest.png");
                surface.setTexture(&texture1);
                surface.setSize(sf::Vector2f(40, 40));
                break;
            case ButtonType::draw:
                surface.setPosition(posX,posY);
                texture2.loadFromFile("./res/dos_rouge.jpg");
                surface.setTexture(&texture2);
                surface.setSize(sf::Vector2f(40, 40));
                break;
            case endOfTurn:
                surface.setPosition(posX,posY);
                texture3.loadFromFile("./res/chest.png");
                surface.setTexture(&texture3);
                surface.setSize(sf::Vector2f(40, 40));
                break;
            case hand:
                surface.setPosition(posX,posY);
                texture4.loadFromFile("./res/chest.png");
                surface.setTexture(&texture4);
                surface.setSize(sf::Vector2f(40, 40));
                break;
            case help:
                surface.setPosition(posX,posY);
                texture5.loadFromFile("./res/help.png");
                surface.setTexture(&texture5);
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
                break;
            case ButtonType::help:
                buttonText = "Ouvre le menu d'aide";
                break;
        }
        std::cout << "Clic sur le bouton : " << buttonText << std::endl;
    }


}
