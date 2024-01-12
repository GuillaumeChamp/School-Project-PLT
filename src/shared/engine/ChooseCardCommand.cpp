#include "ChooseCardCommand.h"

using namespace engine;

// Constructor
ChooseCardCommand::ChooseCardCommand(state::PlayerId authorPlayer, const state::Card &card) : card(card) {
    this->authorPlayer = authorPlayer;
    this->card = card;
    this->commandTypeId = CommandTypeId::CHOOSE_CARD;
}

// Destructor
ChooseCardCommand::~ChooseCardCommand() = default;

// Execute method
void ChooseCardCommand::execute(state::GameState &state) {
    // Getting the player and his hand, and the number of cards in drawableCards
    state::Player player = state.getPlayer(authorPlayer);
    std::vector<state::Card> drawableCards = state.getDrawableCards();
    int nbOfDrawableCards = drawableCards.size();

    // Executing the correct drawing method
    if (nbOfDrawableCards == 3) // If there are 3 possible cards to draw from, it means the player has an Observatory
    {
        auto* command = new GetCardCommand(authorPlayer, card);
        if (command->check(state)){
            command->execute(state);
        }
        delete command;
        // Removing the card from the drawableCards
        long unsigned int i = 0;
        for(; i<drawableCards.size(); i++){
            if  (drawableCards[i].getNameOfCard() == card.getNameOfCard()) {
                break;
            }
        }
        drawableCards.erase(drawableCards.begin()+i);
        state.setDrawableCards(drawableCards);
        // The player has another card to choose after this one so we stay in Draft subphase
        return;
    }
    if (nbOfDrawableCards == 2) // If it's a simple draw of 1 card out of 2 (normal draw or 2nd card of Observatory case)
    {
        auto* command = new GetCardCommand(authorPlayer, card);
        if (command->check(state)){
            command->execute(state);
        }
        delete command;
        // Emptying the drawableCards and changing subphase
        std::vector<state::Card> newDrawableCards;
        state.setDrawableCards(newDrawableCards);
        state.setSubPhase(state::SubPhase::Default);
        player.setDrawAvailability(false);
        state.updatePlayer(player);
        return;
    }
    if (nbOfDrawableCards == 0) // If there are no cards to draw, it means the player just chose a card to build
    {
        auto* command = new BuildCommand(authorPlayer, card);
        if (command->check(state)){
            command->execute(state);
        }
        delete command;
        // Changing the subphase
        state.setSubPhase(state::SubPhase::Default);
    }
}

// Check method
bool ChooseCardCommand::check(state::GameState &state) {
    return Command::check(state);
}
