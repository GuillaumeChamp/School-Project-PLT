#include "InteractiveElement.h"
#include <SFML/Graphics.hpp>

namespace render {
    sf::RectangleShape InteractiveElement::surface;
    
    InteractiveElement::InteractiveElement (int posX, int posY){
        surface.setPosition(posX, posY);

    }
    sf::RectangleShape InteractiveElement::getSurface (){
        return this->surface;
    }

    void InteractiveElement::setSurface (int posX, int posY){
        surface.setPosition(posX, posY);
    }

    bool InteractiveElement::checkClick(sf::Vector2f mousePos) {
        return surface.getGlobalBounds().contains(mousePos);
    }

    void InteractiveElement::checkHover(sf::Vector2f mousePos) {
        if (surface.getGlobalBounds().contains(mousePos)) {
            onHoverAction();
        }
    }

    void InteractiveElement::onClickEvent() {
    }

    void InteractiveElement::onHoverAction() {
    }
}
