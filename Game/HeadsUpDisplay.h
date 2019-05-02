#ifndef HEADSUPDISPLAY_H_INCLUDED
#define HEADSUPDISPLAY_H_INCLUDED
#include "Common/StaticServiceLocator.h"
#include "Game/Event/EntityDeadEvent.h"

namespace Game {
class HUD : public EventListener {
private:
    GraphicsObject *text = NULL;
    int pointCount;
public:
    HUD() : pointCount(0) {
        text = StaticServiceLocator::getGraphicsService()->createTextObject("0000", 0xFF, 0xFF, 0xFF);
        StaticServiceLocator::getEventBus()->addEventListener(this);
    }

    ~HUD() {
        StaticServiceLocator::getEventBus()->removeEventListener(this);
    }

    void paint() {
        text->renderObject(10, 10, 0);
    }

    void eventOcurred(Event* event) {
        if (event->EVENT_TYPE != ENTITY_DEAD) {
            return;
        }
        EntityDeadEvent *ede = (EntityDeadEvent*) event;
        if (ede->ENTITY_ID == -1) {
            return;
        }
        pointCount += 100;
        std::string pointString = std::to_string(pointCount);
        delete text;
        text = StaticServiceLocator::getGraphicsService()->createTextObject(pointString, 0xFF, 0xFF, 0xFF);
    }
};
}
#endif // HEADSUPDISPLAY_H_INCLUDED
