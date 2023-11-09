#include "Card.h"

#include <utility>

class Card{

};
namespace state {

Card::Card(std::string name, state::CardType color, int cost){
    this->nameOfCard = std::move(name);
    this->colorOfCard = color;
    this->costOfCard = cost;
}

Card::~Card()=default;

std::string Card::getNameOfCard() {
    return this->nameOfCard;
}

CardType Card::getColorOfCard(){
    return this->colorOfCard;
}

int Card::getCostOfCard(){
    return this->costOfCard;
}
}