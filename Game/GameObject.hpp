#ifndef GAMEOBJECT_HPP_INCLUDED
#define GAMEOBJECT_HPP_INCLUDED

#include "Game/ObjectState/GameObjectState.h"

namespace Game {

namespace {
    int OBJECT_COUNTER = 0;
}

class GameObject {
private:
    GameObjectState *objectState = NULL;
public:
    const int objectId = ++OBJECT_COUNTER;
    int xCoord;
    int yCoord;
    int xDelta;
    int yDelta;

    GameObject(GameObjectState *objectState_, int x, int y);
    ~GameObject();
    void setState(GameObjectState *objectState_);
    void render();
    int getWidth();
    int getHeight();
    void update();
};

}

#endif // GAMEOBJECT_HPP_INCLUDED
