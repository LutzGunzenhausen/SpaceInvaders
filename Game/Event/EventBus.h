#ifndef EVENTBUS_H_INCLUDED
#define EVENTBUS_H_INCLUDED

#include "Game/Event/Event.h"
#include "Game/Event/EventListener.h"
namespace Game {

class EventBus {
private:
    EventListener **listenerArray = NULL;
    const int MAX_LISTENER_COUNT = 10;
public:
    EventBus() {
        listenerArray = new EventListener*[MAX_LISTENER_COUNT];
        for (int i = 0; i < MAX_LISTENER_COUNT; i++) {
            listenerArray[i] = NULL;
        }
    }

    void addEventListener(EventListener *listener) {
        for (int i = 0; i < MAX_LISTENER_COUNT; i++) {
            if (listenerArray[i] == NULL) {
                listenerArray[i] = listener;
                break;
            }
        }
    }

    void removeEventListener(EventListener *listener) {
        for (int i = 0; i < MAX_LISTENER_COUNT; i++) {
            if (listenerArray[i] != NULL
                 && listenerArray[i] == listener) {
                listenerArray[i] = NULL;
                break;
            }
        }
    }

    void publishEvent(Event *event) {
        for (int i = 0; i < MAX_LISTENER_COUNT; i++) {
            if (listenerArray[i] != NULL) {
                listenerArray[i]->eventOcurred(event);
            }
        }
    }
};

}

#endif // EVENTBUS_H_INCLUDED
