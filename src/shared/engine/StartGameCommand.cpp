
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

    
  } 

  // Serialize method
  void StartGameCommand::serialize() { 
  }

  // Check method
  bool StartGameCommand::check(state::GameState& state) {
    
    return Command::check(state);
    
  }

} // namespace engine
