// ClaimBuildingGold.cpp
#include "ClaimBuildingGold.h"

namespace engine {

    // Constructor
    ClaimBuildingGold::ClaimBuildingGold(state::PlayerId authorPlayer) {
        this->authorPlayer = authorPlayer;
    }

    // Destructor
    ClaimBuildingGold::~ClaimBuildingGold() {
    }

    // Execute method
    void ClaimBuildingGold::execute(state::GameState &state) {
    }

    // Serialize method
    void ClaimBuildingGold::serialize() {
    }

    bool ClaimBuildingGold::check(state::GameState &state) {
        Command::check(state);
    }

} // namespace engine
