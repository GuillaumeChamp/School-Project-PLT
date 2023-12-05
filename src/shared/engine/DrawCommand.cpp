// DrawCommand.cpp
#include "DrawCommand.h"

namespace engine {

  // Constructor
  DrawCommand::DrawCommand(state::PlayerId authorPlayer, state::PlayerId targetPlayer, int nbOfCards) {
    this->authorPlayer = authorPlayer;
    this->targetPlayer = authorPlayer;
    this->nbOfCards = nbOfCards;
  }

  // Destructor
  DrawCommand::~DrawCommand() {
  }

  // Execute method
  void DrawCommand::execute(state::GameState state) {
    // Getting the player to execute the command on
    state::Player player = state.getPlayer(authorPlayer);

    // Getting his hand
    std::vector<state::Card> hand = player.getHand();

    // Getting the stack
    std::vector<state::Card> stack = state.getStack();

    //Checking that the stack has enough cards to draw from
    //if not, re-initializing the stack
    if (stack.size() < nbOfCards){
      //init stack
    }
    else if (stack.size() == nbOfCards)
    {
      //draw the cards then init stack
    }
    else
    {
      //
      std::vector<state::Card> firstTwoCards (stack.begin(), stack.begin() + 2);
      stack.erase(stack.begin(), stack.begin() + 2);
    }

    // Adding the new cards to the player's hand
    //for (state::Card card : firstTwoCards){


    //}

    // Setting the player's new hand and the new stack
    player.setHand(hand);
    state.setStack(stack);
  }

  // Serialize method
  void DrawCommand::serialize() {
  }


} // namespace engine
