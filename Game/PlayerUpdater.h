#ifndef PLAYERUPDATER_H_INCLUDED
#define PLAYERUPDATER_H_INCLUDED

#include "Game/GameObject.hpp"
#include "Common/Constants.h"
#include "Game/Event/EventBus.h"

namespace Game {

class PlayerUpdater : public Updater {
private:
    GameObject *playerObject = NULL;
    bool spaceWasReleased;
public:
    PlayerUpdater(GameObject *playerObject_)
        : playerObject(playerObject_), spaceWasReleased(true) {
    }
    void update(InputMask *inputMask) {
        if (inputMask->isLeftActive()) {
            playerObject->xDelta = -PLAYER_X_SPEED;
        } else if (inputMask->isRightActive()) {
            playerObject->xDelta = PLAYER_X_SPEED;
        } else {
            playerObject->xDelta = 0;
        }
        if (inputMask->isSpaceActive()) {
            if (spaceWasReleased) {
                StaticServiceLocator::getEventBus()->publishEvent(
                    new Event(PLAYER_FIRES_BULLET));
                spaceWasReleased = false;
            }
        }  else {
            spaceWasReleased = true;
        }
    }
};
}
#endif // PLAYERUPDATER_H_INCLUDED
