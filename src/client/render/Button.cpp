#include "Button.h"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace render {
    Button::Button(buttonType buttonType, int posX, int posY):InteractiveElement(posX, posY) {
        sf::Texture  texture1, texture2, texture3, texture4, texture5;

        switch (buttonType){
            case bank:
                surface.setPosition(posX,posY);
                texture1.loadFromFile("../res/1.jpg");
                surface.setTexture(&texture1);
                surface.setSize(sf::Vector2f(40, 40));
                break;
            case draw:
                surface.setPosition(posX,posY);
                texture2.loadFromFile("");
                surface.setTexture(&texture2);
                surface.setSize(sf::Vector2f(40, 40));
                break;
            case endOfTurn:
                surface.setPosition(posX,posY);
                texture3.loadFromFile("");
                surface.setTexture(&texture3);
                surface.setSize(sf::Vector2f(40, 40));
                break;
            case hand:
                surface.setPosition(posX,posY);
                texture4.loadFromFile("");
                surface.setTexture(&texture4);
                surface.setSize(sf::Vector2f(40, 40));
                break;
            case help:
                surface.setPosition(posX,posY);
                texture5.loadFromFile("");
                surface.setTexture(&texture5);
                surface.setSize(sf::Vector2f(40, 40));
                break;
        }
    }

    Button::~Button() {
    }

    void Button::onHoverAction() {
        IHMState::GetInstance() -> hoverButton = this;
    }

    void Button::onClickEvent() {
        std::string buttonText;
        switch (name) {
            case buttonType::bank:
                buttonText = "Recevez deux pièces d'or";
                break;
            case buttonType::draw:
                buttonText = "Piochez une carte parmis 2";
                break;
            case buttonType::endOfTurn:
                buttonText = "Fin du tour";
                break;
            case buttonType::hand:
                buttonText = "Ouvre la main du joueur";
                break;
            case buttonType::help:
                buttonText = "Ouvre le menu d'aide";
                break;
        }
        std::cout << "Clic sur le bouton : " << buttonText << std::endl;
    }

    bool Button::isButtonRender() {
        return isAvailable;
    }

    void Button::setButtonRender(bool isAvailable) {
        this->isAvailable = isAvailable;
    }
}
