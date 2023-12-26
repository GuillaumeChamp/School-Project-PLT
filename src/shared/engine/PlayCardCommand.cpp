#include "PlayCardCommand.h"

namespace engine {

    // Constructor

    // Destructor
    PlayCardCommand::~PlayCardCommand() = default;

    // Execute method
    void PlayCardCommand::execute(state::GameState& state) {
        // 
        auto* command = new ChooseCardCommand(authorPlayer, card);
        Engine::getInstance(state).addCommand(command);
    }

    // Check method
    bool PlayCardCommand::check(state::GameState& state) {
        return true;
    }

} // namespace engine
