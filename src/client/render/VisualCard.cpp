#include "VisualCard.h"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace render {
    VisualCard::VisualCard(std::string filename, int posX, int posY):InteractiveElement(posX, posY)  {
        this->name = filename;
        surface.setPosition(posX, posY);
        surface.setSize(sf::Vector2f(80, 124));
    }

    VisualCard::~VisualCard() {
    }

    void VisualCard::onHoverEvent() {
        IHMState::getInstance()->hoverCard = this;
    }

    void VisualCard::onClickEvent() {
        std::cout << "Clic sur la carte : " << name << std::endl;
    }
    void VisualCard::draw(sf::RenderWindow& window){

        sf::Texture texture;
        std::string Path = "./../res/" + name + ".jpg";
        texture.loadFromFile(Path);
        this->surface.setTexture(&texture);
        window.draw(this->getSurface());
    }
}
