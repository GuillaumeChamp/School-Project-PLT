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
    DrawCommand::~DrawCommand() {
    }

    // Execute method
    void DrawCommand::execute(state::GameState &state) {
        // Getting the player to execute the command on
        state::Player player = state.getPlayer(authorPlayer);

        // Getting his hand
        std::vector<state::Card> hand = player.getHand();

        // Getting the stack
        std::vector<state::Card> stack = state.getStack();

        std::vector<state::Card> drawnCards;

        //Checking that the stack has enough cards to draw from
        if (stack.size() < nbOfCards) //if not, re-initializing the stack then drawing the cards
        {
            StackUtils::initStack();
            drawnCards.insert(drawnCards.end(), stack.begin(), stack.begin() + nbOfCards);
            stack.erase(stack.begin(), stack.begin() + nbOfCards);
        } else if (stack.size() == nbOfCards) // if just enough, drawning the cards then re-initializing the stack
        {
            drawnCards.insert(drawnCards.end(), stack.begin(), stack.begin() + nbOfCards);
            StackUtils::initStack();
        } else // if yes, just draw the cards
        {
            drawnCards.insert(drawnCards.end(), stack.begin(), stack.begin() + nbOfCards);
            stack.erase(stack.begin(), stack.begin() + nbOfCards);
        }

        // Adding the new cards to the player's hand
        for (state::Card card: drawnCards) {
            hand.insert(hand.end(), card);
        }

        // Setting the player's new hand and the new stack
        player.setHand(hand);
        state.setStack(stack);
        state.updatePlayer(player);
    }

    // Check method
    bool DrawCommand::check(state::GameState &state) {
        return Command::check(state);
    }


} // namespace engine
