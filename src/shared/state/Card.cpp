#include "Card.h"

class Card{

};
namespace state {

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