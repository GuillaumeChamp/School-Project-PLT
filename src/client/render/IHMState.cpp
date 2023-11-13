#include "IHMState.h"

namespace render {
  IHMState::IHMState() :
    isHandDisplayed(false),
    isHelpDisplayed(false),
    hoverCard(nullptr),
    hoverButton(nullptr) {
  }

  IHMState* IHMState::getInstance() {
    if (!INSTANCE) {
      INSTANCE = new IHMState();
    }
    return INSTANCE;
  }

  IHMState* IHMState::INSTANCE = nullptr;
}
