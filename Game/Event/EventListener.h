#ifndef EVENTLISTENER_H_INCLUDED
#define EVENTLISTENER_H_INCLUDED

#include "Game/Event/Event.h"

namespace Game {
class EventListener {
public:
    virtual ~EventListener() {
    }
    virtual void eventOcurred(Event* event) = 0;
};
}


#endif // EVENTLISTENER_H_INCLUDED
