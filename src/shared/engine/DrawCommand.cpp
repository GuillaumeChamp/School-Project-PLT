// DrawCommand.cpp
#include "DrawCommand.h"
#include "list"

using namespace engine;

// Constructor
DrawCommand::DrawCommand(state::PlayerId authorPlayer) {
    this->authorPlayer = authorPlayer;
    this->targetPlayer = authorPlayer;
    this->commandTypeId = CommandTypeId::DRAW_CARD;
}

// Destructor
DrawCommand::~DrawCommand() = default;

// Execute method
void DrawCommand::execute(state::GameState &state) {
    // Init variable and query data
    state::Player player = state.getPlayer(authorPlayer);
    std::vector<state::Card> hand = player.getHand();
    std::vector<state::Card> board = player.getBoardOfPlayer();
    std::list<state::Card> stack = state.getStack();

    std::vector<state::Card> drawnCards;
    
    int nbOfCards = 2; // The number of cards to draw is 2 for all the cases except :
    for (const auto& card : board) {
        if (card.getNameOfCard() == "22") { // If the player has the Observatory card
            nbOfCards = 3; // In which case he can draw 2 cards out of 3
            break;
        }
    } 

    //Checking that the stack has enough cards to draw from
    if ((int) stack.size() < nbOfCards) { //if not, re-initializing the stack
        stack = StackUtils::initStack();
    }
    // Then drawing the cards
    for (int i=0; i<nbOfCards; i++){
        state::Card c = stack.back();
        drawnCards.push_back(c);
        stack.pop_back();
    }

    
    // Special cases where the cards can go directly to the player's hand

    // Checking if he has a Library Card
    bool hasLibrary = false;
    for (const auto& card : board) {
        if (card.getNameOfCard() == "Bibliothèque") {
            hasLibrary = true;
            break;
        }
    }

    // And Checking if he is the Architect with his power available
    if ((player.getCharacter() == state::CharacterType::ARCHITECT) and player.isCapacityAvailable())
    {
        // Adding the new cards to the player's hand
        for(state::Card card : drawnCards){
            hand.insert(hand.end(), card);
        }
        
        // Setting the player's new hand and power availability and updating the state
        player.setHand(hand);
        player.setCapacityAvailability(false);
        state.updatePlayer(player);
        // In the case of the Architect, he keeps his drawing availability
        drawnCards.clear();
    }
    else if (hasLibrary) // Checking the library after in case an Architect has it
    {
        // Adding the new cards to the player's hand
        for(state::Card card : drawnCards){
            hand.insert(hand.end(), card);
        }
        
        // Setting the player's new hand, his draw availability and updating the state
        player.setHand(hand);
        player.setDrawAvailability(false);
        state.updatePlayer(player);
        drawnCards.clear();
    }

    // Updating the state
    state.setDrawableCards(drawnCards);
    state.setStack(stack);

    if (drawnCards.size()>0){ // If there is a choice to make (ie : not Architect or library cases) :
        // Switching to draft subphase to trigger a player's choice between the possible cards
        state.setSubPhase(state::SubPhase::PreDraw);
    }
}

// Check method
bool DrawCommand::check(state::GameState &state) {
    return Command::check(state) && state.getPlayer(authorPlayer).isDrawAvailable();
}


