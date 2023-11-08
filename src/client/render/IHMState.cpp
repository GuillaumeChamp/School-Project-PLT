#include "IHMState.h"

namespace render {

IHMState* IHMState::INSTANCE = nullptr;

// Constructor
IHMState::IHMState() : hoverCard(nullptr), hoverButton(nullptr) {
    
}


IHMState* IHMState::GetInstance(const std::string& value) {
    if (INSTANCE == nullptr) {
        INSTANCE = new IHMState();
    }


    return INSTANCE;
}

} 
