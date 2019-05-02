#ifndef GAMEOBJECTSTATE_CPP_INCLUDED
#define GAMEOBJECTSTATE_CPP_INCLUDED

#include "Game/ObjectState/GameObjectState.h"
#include "Common/Graphics/AlignmentUtils.h"
#include "Common/Graphics/GraphicsObject.h"
namespace Game {


    GameObjectState::GameObjectState(GraphicsObject *graphicsObject_) : GameObjectState(graphicsObject_, 0) {
    }

    GameObjectState::GameObjectState(GraphicsObject *graphicsObject_, int delay_)
     : graphicsObject(graphicsObject_), imageCount(graphicsObject_->getTileCount()),
      delay(delay_), imageIndex(0), updateIndex(0) {
    }

    void GameObjectState::update() {
        if (imageCount == 1) {
            return;
        }
        if (AlignmentUtils::getPassedDuration(updateIndex++) > delay) {
            imageIndex = (imageIndex + 1) % imageCount;
            updateIndex = 0;
            if (imageIndex == 0) {
                animationFinished();
            }
        }
    }

    void GameObjectState::render(int x, int y) {
        graphicsObject->renderObject(x, y, imageIndex);
    }

    int GameObjectState::getWidth() {
        return graphicsObject->width;
    }

    int GameObjectState::getHeight() {
        return graphicsObject->height;
    }

}

#endif // GAMEOBJECTSTATE_CPP_INCLUDED
