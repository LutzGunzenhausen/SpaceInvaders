#ifndef PHYSICSSERVICE_H_INCLUDED
#define PHYSICSSERVICE_H_INCLUDED

#include "Game/GameObject.hpp"

namespace Game {

class PhysicsService {
public:
    virtual void update(GameObject *graphicsObject) = 0;
};

}

#endif // PHYSICSSERVICE_H_INCLUDED
