#include "InteractiveElement.h"


namespace render {
    
    InteractiveElement::InteractiveElement (int posX, int posY){
        this->surface = sf::RectangleShape();
        this->surface.setPosition(posX, posY);
    }

    InteractiveElement::~InteractiveElement(){
        
    }

    sf::RectangleShape InteractiveElement::getSurface() const{
        return this->surface;
    }


    bool InteractiveElement::checkClick(int x,int y) {
        return surface.getGlobalBounds().contains(x,y);
    }

    bool InteractiveElement::checkHover(int x,int y) {
        return (surface.getGlobalBounds().contains(x,y));
    }

    void InteractiveElement::onClickEvent() {
    }

    void InteractiveElement::onHoverEvent() {
    }
}
