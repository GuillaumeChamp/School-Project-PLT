#include "VisualCard.h"
#include <iostream>
#include <utility>
#include "config.h"

using namespace render;

VisualCard::VisualCard(std::string filename, float posX, float posY) : InteractiveElement(posX, posY) {
    this->name = std::move(filename);
    surface.setPosition(posX, posY);
    surface.setSize(sf::Vector2f(80, 124));
}

VisualCard::~VisualCard() = default;

std::string VisualCard::onHoverEvent() {
    IHMState::getInstance()->hoverCard = this;
}

std::string VisualCard::onClickEvent() {
    return name;
}

void VisualCard::zoomCard() {
    this->surface.setPosition(680, 350);
    this->surface.setSize(sf::Vector2f(240, 312));
}

void VisualCard::draw(sf::RenderWindow &window) {
    sf::Texture texture;
    std::string path = RES_DIR;
    path.append(name).append(".png");
    texture.loadFromFile(path);
    this->surface.setTexture(&texture);
    window.draw(this->getSurface());
}

