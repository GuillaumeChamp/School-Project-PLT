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
        std::vector<state::Card> drawableCards;

        // Checking that the stack has enough cards to draw from
        if (stack.size() < nbOfCards) { // if not, re-initializing the stack
            stack = StackUtils::initStack();
            //TODO replace stack by list because erase is heavy after finishing stack related command
        }

        // Getting the drawable cards from the stack
        drawableCards.insert(drawableCards.end(), stack.begin(), stack.begin() + nbOfCards);
        stack.erase(stack.begin(), stack.begin() + nbOfCards);

        // Update the state
        state.setDrawableCards(drawableCards);
        state.setStack(stack);
        state.updatePlayer(player);
    }

    // Check method
    bool DrawCommand::check(state::GameState &state) {
        return Command::check(state) && state.getPlayer(authorPlayer).isDrawAvailable();
    }


} // namespace engine
