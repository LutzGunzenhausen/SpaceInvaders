#ifndef SPACEINVADERSSTATE_CPP_INCLUDED
#define SPACEINVADERSSTATE_CPP_INCLUDED

#include "Game/State/SpaceInvadersState.hpp"
#include "Common/StaticServiceLocator.h"
#include "Game/PlayerUpdater.h"
#include "Game/EnemiesUpdater.h"
#include "Game/State/MenuState.hpp"
#include "Game/ObjectState/GameObjectState.h"
#include "Game/Event/EntityDeadEvent.h"
#include "Game/Event/EnemyFiresBulletEvent.h"
#include "Game/ObjectState/EventTriggeringState.h"

#define GET_GRAPHICS(x) StaticServiceLocator::getGraphicsResourceStorage()->getGraphicsObject(x)

namespace Game {

    SpaceInvadersState::SpaceInvadersState() : pause(false), lost(false), won(false) {
        GraphicsObject *enemyGraph = GET_GRAPHICS(SPACE_INVADER);
        GraphicsObject *playerGraph = GET_GRAPHICS(PLAYER);
        hud = new HUD();

        enemies = new GameObject*[ENEMY_COUNT];
        int yCoord = ENEMY_START_Y;
        for (int row = 0, index = 0; row < ENEMY_ROW_COUNT; row++) {
            int xCoord = ENEMY_START_X;
            for (int column = 0; column < ENEMY_COLUMN_COUNT; column++, index++) {
                GameObject *enemy = new GameObject(new GameObjectState(enemyGraph, 1000), xCoord, yCoord);
                enemies[index] = enemy;
                xCoord += enemyGraph->width + ENEMY_HORIZONTAL_GAP;
            }
            yCoord += enemyGraph->height + ENEMY_VERTICAL_GAP;
        }

        player = new GameObject(new GameObjectState(playerGraph), 100, 100);
        player->xCoord = PLAYER_X_COORD_START;
        player->yCoord = PLAYER_Y_COORD_START;
        enemiesUpdater = new EnemiesUpdater(enemies, player);
        playerUpdater = new PlayerUpdater(player);
        SpaceInvadersListener *newListener = new SpaceInvadersListener();
        newListener->state = this;
        listener = newListener;
        StaticServiceLocator::getEventBus()->addEventListener(listener);
    }

    SpaceInvadersState::~SpaceInvadersState() {
        StaticServiceLocator::getEventBus()->removeEventListener(listener);
        delete listener;
        listener = NULL;
        delete hud;
        hud = NULL;
        delete player;
        player = NULL;
        for (int i = 0; i < ENEMY_COUNT; i++) {
            if (enemies[i] != NULL) {
                delete enemies[i];
                enemies[i] = NULL;
            }
        }
        delete[] enemies;
        delete playerUpdater;
        delete enemiesUpdater;
        if (bullet != NULL) {
            delete bullet;
        }
        if (enemyBullet != NULL) {
            delete enemyBullet;
        }
    }

    GameState* SpaceInvadersState::update(InputMask *inputMask) {
        if (inputMask->isESCActive()) {
            return new MenuState();
        } else if (inputMask->isF2Active()) {
            return new SpaceInvadersState();
        } else if (inputMask->isPauseActive()) {
            pause = !pause;
        }

        if (pause || lost || won) {
            return NULL;
        }

        player->update();
        playerUpdater->update(inputMask);
        enemiesUpdater->update(inputMask);
        StaticServiceLocator::getPhysicsService()->update(player);
        for (int i = 0; i < ENEMY_COUNT; i++) {
            if (enemies[i] != NULL) {
                StaticServiceLocator::getPhysicsService()->update(enemies[i]);
                enemies[i]->update();
            }
        }

        if (bullet != NULL) {
            StaticServiceLocator::getPhysicsService()->update(bullet);
            if (bullet->yCoord == 0) {
                delete bullet;
                bullet = NULL;
            } else {
                for (int i = 0; i < ENEMY_COUNT; i++) {
                    if (enemies[i] != NULL) {
                        if (checkCollision(bullet, enemies[i])) {
                            LOG_MESSAGE("Collision found!");
                            StaticServiceLocator::getGraphicsResourceStorage(
                                )->getAudioObject(EXPLOSION_SOUND)->play();
                            delete bullet;
                            bullet = NULL;
                            Event *event = new EntityDeadEvent(enemies[i]->objectId);
                            GraphicsObject *graphics = GET_GRAPHICS(EXPLOSION);
                            GameObjectState *state = new EventTriggeringState(graphics, 55, event);
                            enemies[i]->setState(state);
                            break;
                        }

                    }
                }
            }

        }
        if (enemyBullet != NULL) {
            StaticServiceLocator::getPhysicsService()->update(enemyBullet);
            if (checkCollision(enemyBullet, player)) {
                StaticServiceLocator::getGraphicsResourceStorage()->getAudioObject(EXPLOSION_SOUND)->play();
                Event *event = new EntityDeadEvent(-1);
                GraphicsObject *graphics = GET_GRAPHICS(EXPLOSION);
                GameObjectState *state = new EventTriggeringState(graphics, 55, event);
                player->setState(state);
            }
            if (enemyBullet->yCoord + enemyBullet->getHeight() == WINDOW_HEIGHT) {
                delete enemyBullet;
                enemyBullet = NULL;
            }
        }
        return NULL;
    }

    void SpaceInvadersState::paint() {
        //LOG_MESSAGE("Game");
        for (int i = 0; i < ENEMY_COUNT; i++) {
            if (enemies[i] != NULL) {
                enemies[i]->render();
            }
        }
        hud->paint();
        LOG_MESSAGE("Draw Player!");
        player->render();
        if (bullet != NULL) {
            bullet->render();
        }
        if (enemyBullet != NULL) {
            enemyBullet->render();
        }
        if (pause) {
            GraphicsObject *pauseMessage = GET_GRAPHICS(PAUSE_MESSAGE);
            int xCoord = AlignmentUtils::centerAroundCoordinate(pauseMessage, WINDOW_WIDTH / 2);
            pauseMessage->renderObject(xCoord, WINDOW_HEIGHT / 2, 0);
        }
        if (lost || won) {
            LOG_MESSAGE("Lost");
            GraphicsObject *lostMessage =
                lost ? GET_GRAPHICS(LOST_MESSAGE) : GET_GRAPHICS(WON_MESSAGE);
            int xCoord = AlignmentUtils::centerAroundCoordinate(lostMessage, WINDOW_WIDTH / 2);
            lostMessage->renderObject(xCoord, WINDOW_HEIGHT / 2, 0);
            LOG_MESSAGE("Lost shown");
        }
    }

    void SpaceInvadersState::listenForEvents(Event* event) {
        LOG_MESSAGE("Event!!!");
        if (event->EVENT_TYPE == PLAYER_FIRES_BULLET) {
            LOG_MESSAGE("Player Fires");
            if (bullet == NULL) {
                GraphicsObject *graphics = GET_GRAPHICS(BULLET);
                int xCoord = player->xCoord + (player->getWidth() / 2);
                bullet = new GameObject(new GameObjectState(graphics), xCoord, player->yCoord);
                bullet->yDelta = BULLET_SPEED;
                StaticServiceLocator::getGraphicsResourceStorage()->getAudioObject(SHOT_SOUND)->play();
                LOG_MESSAGE("Player Fired");
            }
        } else if (event->EVENT_TYPE == ENTITY_DEAD) {
            LOG_MESSAGE("Enemy dies");
            EntityDeadEvent *entityDead = (EntityDeadEvent*) event;
            if (entityDead->ENTITY_ID == -1) {
                lost = true;
                LOG_MESSAGE("Failure");
                StaticServiceLocator::getGraphicsResourceStorage(
                    )->getAudioObject(FAILURE_SOUND)->play();
                return;
            }

            int enemiesFound = 0;
            for (int i = 0; i < ENEMY_COUNT; i++) {
                if (enemies[i] != NULL) {
                    enemiesFound++;
                    if (enemies[i]->objectId == entityDead->ENTITY_ID) {
                        delete enemies[i];
                        enemies[i] = NULL;
                        LOG_MESSAGE("Enemy died");
                    }
                }
            }
            if (enemiesFound == 1) {
                won = true;
                StaticServiceLocator::getGraphicsResourceStorage(
                    )->getAudioObject(SUCCESS_SOUND)->play();
            }
        } else if (event->EVENT_TYPE == ENEMY_FIRES_BULLET) {
            LOG_MESSAGE("Enemy fires");
            EnemyFiresBulletEvent *fireEvent = (EnemyFiresBulletEvent*) event;
            GraphicsObject *graphics = GET_GRAPHICS(BULLET);
            int xCoord = fireEvent->startXCoord;
            int yCoord = fireEvent->startYCoord;
            enemyBullet = new GameObject(new GameObjectState(graphics), xCoord, yCoord);
            enemyBullet->yDelta = -BULLET_SPEED;
            StaticServiceLocator::getGraphicsResourceStorage()->getAudioObject(SHOT_SOUND)->play();
            LOG_MESSAGE("Enemy fired");
        } else if (event->EVENT_TYPE == GROUND_REACHED) {
            LOG_MESSAGE("Ground reached");
            StaticServiceLocator::getGraphicsResourceStorage(
                    )->getAudioObject(FAILURE_SOUND)->play();
            lost = true;
        }
    }

    void SpaceInvadersListener::eventOcurred(Event *event) {
        state->listenForEvents(event);
    }

    bool SpaceInvadersState::checkCollision(GameObject *bullet, GameObject *possibleTarget) {
        if (bullet->xCoord > possibleTarget->xCoord + possibleTarget->getWidth()) {
            // too far right
            return false;
        } else if (bullet->yCoord > possibleTarget->yCoord + possibleTarget->getHeight()) {
            // too far below
            return false;
        } else if (bullet->xCoord + bullet->getWidth() < possibleTarget->xCoord) {
            // too far left
            return false;
        } else if (bullet->yCoord + bullet->getHeight() < possibleTarget->yCoord) {
            // too far above
            return false;
        }
        return true;
    }

}
#endif // SPACEINVADERSSTATE_CPP_INCLUDED
