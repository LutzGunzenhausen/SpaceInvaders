#ifndef GAMEOBJECT_CPP_INCLUDED
#define GAMEOBJECT_CPP_INCLUDED

#include "Game/ObjectState/GameObjectState.h"
#include "Common/Graphics/AlignmentUtils.h"
namespace Game {

    GameObject::GameObject(GameObjectState *objectState_, int x, int y)
     : objectState(objectState_), xCoord(x), yCoord(y), xDelta(0), yDelta(0)
       {
    }

    GameObject::~GameObject() {
        delete objectState;
        objectState = NULL;
    }

    void GameObject::setState(GameObjectState *objectState_) {
        objectState = objectState_;
    }

    void GameObject::render() {
        objectState->render(xCoord, yCoord);
    }

    int GameObject::getWidth() {
        return objectState->getWidth();
    }

    int GameObject::getHeight() {
        return objectState->getHeight();
    }

    void GameObject::update() {
        objectState->update();
    }


}

#endif // GAMEOBJECT_CPP_INCLUDED
