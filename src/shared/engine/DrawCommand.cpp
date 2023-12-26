// DrawCommand.cpp
#include "DrawCommand.h"
#include "list"

using namespace engine;

// Constructor
DrawCommand::DrawCommand(state::PlayerId authorPlayer, int nbOfCards) {
    this->authorPlayer = authorPlayer;
    this->targetPlayer = authorPlayer;
    this->nbOfCards = nbOfCards;
    this->commandTypeId = CommandTypeId::DRAW_CARD;
}

// Destructor
DrawCommand::~DrawCommand() = default;

// Execute method
void DrawCommand::execute(state::GameState &state) {
    // Init variable and query data
    state::Player player = state.getPlayer(authorPlayer);
    std::list<state::Card> stack = state.getStack();

    std::vector<state::Card> drawnCards;
    //Checking that the stack has enough cards to draw from
    if ((int) stack.size() < nbOfCards) { //if not, re-initializing the stack then drawing the cards
        stack = StackUtils::initStack();
    }
    for (int i=0;i<nbOfCards;i++){
        state::Card c = stack.back();
        drawnCards.push_back(c);
        stack.pop_back();
    }
    // Update the state
    state.setDrawableCards(drawnCards);
    state.setStack(stack);
    state.updatePlayer(player);
}

// Check method
bool DrawCommand::check(state::GameState &state) {
    return Command::check(state) && state.getPlayer(authorPlayer).isDrawAvailable();
}


