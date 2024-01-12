#include "InteractiveElement.h"


using namespace render;

InteractiveElement::InteractiveElement(float posX, float posY) {
    this->surface = sf::RectangleShape();
    this->surface.setPosition(posX, posY);
}

InteractiveElement::~InteractiveElement() = default;

sf::RectangleShape InteractiveElement::getSurface() const {
    return this->surface;
}

bool InteractiveElement::checkClick(float x, float y) {
    return surface.getGlobalBounds().contains(x, y);
}

bool InteractiveElement::checkHover(float x, float y) {
    return surface.getGlobalBounds().contains(x, y);
}

std::string InteractiveElement::onClickEvent() {
    return {};
}

std::string InteractiveElement::onHoverEvent() {
    return {};
}

