
#include "StartGameCommand.h"
#include <iostream>

namespace engine {

  // Constructor
  StartGameCommand::StartGameCommand(state::PlayerId authorPlayer) {

    this->authorPlayer=authorPlayer;

  }

  // Destructor
  StartGameCommand::~StartGameCommand() {
    
  }

  // Execute method
  void StartGameCommand::execute(state::GameState& state){

            //initialisation de type constructeur 
            state.setCurrentCharacter(state::CharacterType::NO_CHARACTER);
            state.setCrownOwner(state::PlayerId::PLAYER_A);
            state.setPlaying(state::PlayerId::PLAYER_A);
            state.setKilledCharacter(state::CharacterType::NO_CHARACTER);
            state.setRobbedCharacter(state::CharacterType::NO_CHARACTER);

            //Initialisation des personnages dispo 
            state.setAvailableCharacter({
             state::CharacterType::ASSASSIN,
             state::CharacterType::THIEF,
             state::CharacterType::MAGICIAN,
             state::CharacterType::KING,
             state::CharacterType::BISHOP,
             state::CharacterType::MERCHANT,
             state::CharacterType::ARCHITECT,
             state::CharacterType::WARLORD});

            // Distribution des cartes
            std::list<state::Card> stack = state.getStack();
            stack = StackUtils::initStack();
            std::vector<state::Card> hand1, hand2, hand3, hand4;
            state::Player player1 = state.getPlayer(state::PLAYER_A);
            state::Player player2 = state.getPlayer(state::PLAYER_B);
            state::Player player3 = state.getPlayer(state::PLAYER_C);
            state::Player player4 = state.getPlayer(state::PLAYER_D);
            for (int i = 0; i<4 ; i++) {
              hand1.push_back(stack.front());
              stack.pop_front();
              hand2.push_back(stack.front());
              stack.pop_front();
              hand3.push_back(stack.front());
              stack.pop_front();
              hand4.push_back(stack.front());
              stack.pop_front();
            }
            player1.setHand(hand1);
            player2.setHand(hand2);
            player3.setHand(hand3);
            player4.setHand(hand4);
            state.updatePlayer(player1);
            state.updatePlayer(player2);
            state.updatePlayer(player3);
            state.updatePlayer(player4);

            //quand toutes les initialisations sont faites 
            //on peut passer à la choose characterPhase automatiquement
            state.setGamePhase(state::Phase::CHOOSE_CHARACTER);
             
  } 

  // Check method
  bool StartGameCommand::check(state::GameState& state) {
    
    return (state.getGamePhase()==state::Phase::START_GAME);
    
  }

} // namespace engine
