#ifndef ALIGNMENTUTILS_H_INCLUDED
#define ALIGNMENTUTILS_H_INCLUDED

#include "Common/Constants.h"
#include "Common/Graphics/GraphicsObject.h"
#include "Game/ObjectState/GameObjectState.h"
#include "Game/GameObject.hpp"

namespace Game {

class AlignmentUtils {

public:
    static inline int centerAroundCoordinate(GraphicsObject *object, int x) {
        return x - (object->width / 2);
    }
    static inline int centerAroundCoordinate(GameObjectState *object, int x) {
        return x - (object->getWidth() / 2);
    }

    static inline int getPassedDuration(int updateFrames) {
        return DELAY_TIME * updateFrames;
    }

    static inline int getDistancePerFrame(int distancePerSecond) {
        return distancePerSecond * (1.0 / FRAMES_PER_SECOND);
    }

    static inline int getMin(int a, int b) {
        return (a < b) ? a : b;
    }

    static inline int getMax(int a, int b) {
        return (a > b) ? a : b;
    }

    static inline int getAbsHorizontalDistance(GameObject *a, GameObject *b) {
        return getAbs(a->xCoord - b->xCoord);
    }

    static inline int getAbs(int a) {
        return a > 0 ? a : -a;
    }
};

}

#endif // ALIGNMENTUTILS_H_INCLUDED
