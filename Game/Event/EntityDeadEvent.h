#ifndef ENTITYDEADEVENT_H_INCLUDED
#define ENTITYDEADEVENT_H_INCLUDED
#include "Game/Event/Event.h"

namespace Game {

class EntityDeadEvent : public Event {

public:
    const int ENTITY_ID;
    EntityDeadEvent(const int entityId) : Event(ENTITY_DEAD), ENTITY_ID(entityId) {
    }
};
}

#endif // ENTITYDEADEVENT_H_INCLUDED
