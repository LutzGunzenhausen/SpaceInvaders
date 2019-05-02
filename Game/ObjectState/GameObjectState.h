#ifndef GAMEOBJECTSTATE_H_INCLUDED
#define GAMEOBJECTSTATE_H_INCLUDED

#include "Common/Graphics/GraphicsObject.h"
#include <iostream>
namespace Game {

class GameObjectState {
private:
    GraphicsObject *graphicsObject = NULL;
    int imageCount;
    int delay;
    int imageIndex;
    int updateIndex;
public:
    GameObjectState(GraphicsObject *graphicsObject_);
    GameObjectState(GraphicsObject *graphicsObject_, int delay_);
    virtual ~GameObjectState() {
    }
    void update();
    void render(int x, int y);
    int getWidth();
    int getHeight();
protected:
    virtual void animationFinished() {
    }
};

}

#endif // GAMEOBJECTSTATE_H_INCLUDED
