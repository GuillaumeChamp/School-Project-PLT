#include "VisualCard.h"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace render {
    VisualCard::VisualCard(std::string filename, int posX, int posY):InteractiveElement(posX, posY)  {
        this->name = filename;
        sf::Texture texture;
        std::string Path = "./res/" + filename + ".jpg";
        texture.loadFromFile(Path);
        surface.setTexture(&texture);
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
}
