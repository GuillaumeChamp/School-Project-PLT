#include "Button.h"
#include <SFML/Graphics/Texture.hpp>
#include "config.h"

using namespace render;

Button::Button(ButtonType buttonType, float posX, float posY) : InteractiveElement(posX, posY) {
    this->name = buttonType;
    this->surface.setPosition(posX, posY);
    this->surface.setSize(sf::Vector2f(50, 50));
}

Button::~Button() = default;

std::string Button::onHoverEvent() {
    IHMState::getInstance()->hoverButton = this;
    return {};
}

std::string Button::onClickEvent() {
    int commandIndex;
    switch (name) {
        case ButtonType::bank:
            commandIndex = 2;
            break;
        case ButtonType::draw:
            commandIndex = 1;
            break;
        case ButtonType::endOfTurn:
            commandIndex = 8;
            break;
        case ButtonType::hand:
            IHMState::getInstance()->isHandDisplayed = !IHMState::getInstance()->isHandDisplayed;
            return "";
        case ButtonType::help:
            IHMState::getInstance()->isHelpDisplayed = !IHMState::getInstance()->isHelpDisplayed;
            return "";
        case ButtonType::capacity:
            IHMState::getInstance()->isCapacityButtonPressed = !IHMState::getInstance()->isCapacityButtonPressed;
            return "";
    }
    return std::to_string(commandIndex);
}

void Button::draw(sf::RenderWindow &render) {
    std::string res = RES_DIR;
    sf::Texture texture;
    switch (this->name) {
        case ButtonType::bank:
            texture.loadFromFile(res + "chest.png");
            break;
        case ButtonType::draw :
            texture.loadFromFile(res + "draw_icon.png");
            break;
        case endOfTurn:
            texture.loadFromFile(res + "end_of_turn_icon.png");
            break;
        case hand:
            texture.loadFromFile(res + "dos.png");
            break;
        case help:
            texture.loadFromFile(res + "help.png");
            break;
        case capacity:
            texture.loadFromFile(res + "capacity.png");
            break;
    }
    this->surface.setTexture(&texture);
    render.draw(surface);
}

ButtonType Button::getType() const {
    return this->name;
}


