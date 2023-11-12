#include "Card.h"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace render {
    Card::Card(std::string filename, int posX, int posY):InteractiveElement(posX, posY)  {
        this->name = filename;
        sf::Texture texture;
        std::string Path = "../res/" + filename + ".jpg";
        texture.loadFromFile(Path);
        surface.setTexture(&texture);
        surface.setPosition(posX, posY);
        surface.setSize(sf::Vector2f(80, 124));
    }

    Card::~Card() {
    }

    void Card::onHoverAction() {
        IHMState::GetInstance()->hoverCard = this;

    }

    void Card::onClickEvent() {
        std::cout << "Clic sur la carte : " << name << std::endl;
    }
}
