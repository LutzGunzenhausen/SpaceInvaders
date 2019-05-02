#ifndef ENEMYFIRESBULLETEVENT_H_INCLUDED
#define ENEMYFIRESBULLETEVENT_H_INCLUDED

#include "Game/Event/Event.h"

namespace Game {

class EnemyFiresBulletEvent : public Event {

public:
    const int startXCoord;
    const int startYCoord;
    EnemyFiresBulletEvent(int xCoord, int yCoord)
     : Event(ENEMY_FIRES_BULLET), startXCoord(xCoord), startYCoord(yCoord) {
    }
};
}

#endif // ENEMYFIRESBULLETEVENT_H_INCLUDED
