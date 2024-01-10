#include "IHMState.h"

using namespace render;

IHMState::IHMState() :
        isHandDisplayed(false),
        isHelpDisplayed(false),
        hoverCard(nullptr),
        hoverButton(nullptr),
        isCapacityButtonPressed(false) {
}

IHMState *IHMState::getInstance() {
    if (!INSTANCE) {
        INSTANCE = new IHMState();
    }
    return INSTANCE;
}

IHMState *IHMState::INSTANCE = nullptr;

