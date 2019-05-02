#ifndef DEFAULTPHYSICSSERVICE_HPP_INCLUDED
#define DEFAULTPHYSICSSERVICE_HPP_INCLUDED

#include "Common/Physics/PhysicsService.h"
#include "Common/Constants.h"
namespace Game {
class DefaultPhysicsService : public PhysicsService {

public:
    void update(GameObject *graphicsObject) {
        int xDelta = AlignmentUtils::getDistancePerFrame(graphicsObject->xDelta);
        int yDelta = AlignmentUtils::getDistancePerFrame(graphicsObject->yDelta);
        int width = graphicsObject->getWidth();
        int height = graphicsObject->getHeight();
        graphicsObject->xCoord += xDelta;
        if (graphicsObject->xCoord < 0) {
            graphicsObject->xCoord = 0;
        } else if (graphicsObject->xCoord + width > WINDOW_WIDTH) {
            graphicsObject->xCoord = WINDOW_WIDTH - width;
        }
        graphicsObject->yCoord += yDelta;
        if (graphicsObject->yCoord < 0) {
            graphicsObject->yCoord = 0;
        } else if (graphicsObject->yCoord + height > WINDOW_HEIGHT) {
            graphicsObject->yCoord = WINDOW_HEIGHT - height;
        }
    }
};

}
#endif // DEFAULTPHYSICSSERVICE_HPP_INCLUDED
