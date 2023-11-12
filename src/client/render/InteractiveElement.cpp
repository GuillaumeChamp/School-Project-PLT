#include "InteractiveElement.h"

namespace render {
    
    InteractiveElement::InteractiveElement (int posX, int posY){
        this->surface = sf::RectangleShape();
        this->surface.setPosition(posX, posY);
    }

    InteractiveElement::~InteractiveElement(){
        
    }

    sf::RectangleShape InteractiveElement::getSurface(){
        return this->surface;
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
