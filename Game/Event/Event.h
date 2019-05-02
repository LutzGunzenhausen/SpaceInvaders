#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include "Common/Constants.h"

namespace Game {

class Event {
public:
    const EventTypes EVENT_TYPE;
    Event(const EventTypes type) : EVENT_TYPE(type) {
    }
    virtual ~Event() {
    }

};
}

#endif // EVENT_H_INCLUDED
