#include "Card.h"

#include <utility>


namespace state {

Card::Card(std::string name, state::CardType color, int cost){
    this->nameOfCard = std::move(name);
    this->colorOfCard = color;
    this->costOfCard = cost;
}

Card::~Card()=default;

std::string Card::getNameOfCard() const{
    return this->nameOfCard;
}

CardType Card::getColorOfCard() const{
    return this->colorOfCard;
}

int Card::getCostOfCard() const{
    return this->costOfCard;
}
}