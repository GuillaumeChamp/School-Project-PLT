#include "Card.h"

class Card{

};
namespace state {

Card::Card(std::string name, state::CardType color, int cost){
    this->nameOfCard = name;
    this->colorOfCard = color;
    this->costOfCard = cost;
}

Card::~Card(){
    //delete &nameOfCard;
}

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