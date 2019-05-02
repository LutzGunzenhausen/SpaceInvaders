#ifndef SPACEINVADERSSTATE_HPP_INCLUDED
#define SPACEINVADERSSTATE_HPP_INCLUDED

#include <iostream>
#include "Game/State/GameState.h"
#include "Game/GameObject.hpp"
#include "Game/Updater.h"
#include "Game/Event/EventListener.h"
#include "Game/Event/Event.h"
#include "Game/HeadsUpDisplay.h"

namespace Game {

class SpaceInvadersState : public GameState {
private:
    GameObject **enemies = NULL;
    GameObject *player = NULL;
    GameObject *bullet = NULL;
    GameObject *enemyBullet = NULL;
    Updater *playerUpdater = NULL;
    Updater *enemiesUpdater = NULL;
    EventListener *listener = NULL;
    HUD *hud = NULL;
    bool pause;
    bool lost;
    bool won;
    bool checkCollision(GameObject *bullet, GameObject *possibleTarget);
public:
    void listenForEvents(Event* event);
    SpaceInvadersState();
    ~SpaceInvadersState();
    GameState* update(InputMask *inputMask);
    void paint();
};

class SpaceInvadersListener : public EventListener {
public:
    SpaceInvadersState *state = NULL;
    void eventOcurred(Event *event);
};

}

#endif // SPACEINVADERSSTATE_HPP_INCLUDED
