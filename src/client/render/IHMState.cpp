#include "IHMState.h"

namespace render {
  IHMState::IHMState() :
    isHandDisplayed(false),
    isHelpDisplayed(false),
    hoverCard(nullptr),
    hoverButton(nullptr) {
  }

  IHMState* IHMState::GetInstance() {
    if (!INSTANCE) {
      INSTANCE = new IHMState();
    }
    return INSTANCE;
  }

  IHMState* IHMState::INSTANCE = nullptr;
}
