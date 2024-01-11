
#include "StartGameCommand.h"

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

            //quand toutes les initialisations sont faites 
            //on peut passer à la choose characterPhase automatiquement
            state.setGamePhase(state::Phase::CHOOSE_CHARACTER);
             
  } 

  // Check method
  bool StartGameCommand::check(state::GameState& state) {
    
    return (state.getGamePhase()==state::Phase::START_GAME);
    
  }

} // namespace engine
