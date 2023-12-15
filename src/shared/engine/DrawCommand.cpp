// DrawCommand.cpp
#include "DrawCommand.h"

namespace engine {

    // Constructor
    DrawCommand::DrawCommand(state::PlayerId authorPlayer, int nbOfCards) {
        this->authorPlayer = authorPlayer;
        this->targetPlayer = authorPlayer;
        this->nbOfCards = nbOfCards;
    }

    // Destructor
    DrawCommand::~DrawCommand() = default;

    // Execute method
    void DrawCommand::execute(state::GameState &state) {
        // Init variable and query data
        state::Player player = state.getPlayer(authorPlayer);
        std::vector<state::Card> stack = state.getStack();

        std::vector<state::Card> drawnCards;
        //Checking that the stack has enough cards to draw from
        if (stack.size() < nbOfCards) { //if not, re-initializing the stack then drawing the cards
            stack = StackUtils::initStack();
            drawnCards.insert(drawnCards.end(), stack.begin(), stack.begin() + nbOfCards);
            stack.erase(stack.begin(), stack.begin() + nbOfCards);
            //TODO replace stack by list because erase is heavy after finishing stack related command
        } else {// if yes, just draw the cards
            drawnCards.insert(drawnCards.end(), stack.begin(), stack.begin() + nbOfCards);
            stack.erase(stack.begin(), stack.begin() + nbOfCards);
        }

        // Update the state
        state.setDrawableCards(drawnCards);
        state.setStack(stack);
        state.updatePlayer(player);
    }

    // Serialize method
    void DrawCommand::serialize() {
    }

    bool DrawCommand::check(state::GameState &state) {
        return Command::check(state) && state.getPlayer(authorPlayer).isDrawAvailable();
    }


} // namespace engine
