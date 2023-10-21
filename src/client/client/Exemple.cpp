#include <state/ActivePlayer.h>  // Included from library shared_static
#include "Exemple.h"

namespace client {

void Exemple::setX (int x) {
    // Create an object from "shared" library
    state::ActivePlayer y {};
    y.getHand();

    this->x = x;
}

}

