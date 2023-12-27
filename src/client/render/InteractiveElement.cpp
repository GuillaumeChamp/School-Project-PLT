#include "InteractiveElement.h"


namespace render {
    
    InteractiveElement::InteractiveElement (float posX, float posY){
        this->surface = sf::RectangleShape();
        this->surface.setPosition(posX, posY);
    }

    InteractiveElement::~InteractiveElement()= default;

    sf::RectangleShape InteractiveElement::getSurface() const{
        return this->surface;
    }

    bool InteractiveElement::checkClick(float x,float y) {
        return surface.getGlobalBounds().contains(x,y);
    }

    bool InteractiveElement::checkHover(float x,float y) {
        return surface.getGlobalBounds().contains(x,y);
    }

    void InteractiveElement::onClickEvent() {
    }

    void InteractiveElement::onHoverEvent() {
    }
}
