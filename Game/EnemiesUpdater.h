#ifndef ENEMIESUPDATER_H_INCLUDED
#define ENEMIESUPDATER_H_INCLUDED

#include "Common/Constants.h"
#include "Game/Updater.h"
#include "Game/GameObject.hpp"
#include "Common/Graphics/AlignmentUtils.h"
#include "Common/StaticServiceLocator.h"
#include "Game/Event/EnemyFiresBulletEvent.h"

namespace Game {

class EnemiesUpdater : public Updater {
private:
    GameObject **enemies;
    GameObject *player;
    bool lastDirectionLeft;
    int updateCount;
public:
    EnemiesUpdater(GameObject **enemies_, GameObject *player_)
     : enemies(enemies_), player(player_), lastDirectionLeft(false), updateCount(0) {
    }

    void update(InputMask *inputMask) {
        int minXCoord = WINDOW_WIDTH;
        int maxXCoord = 0;
        int minDistance = WINDOW_WIDTH;
        int startXCoord = 0;
        int startYCoord = 0;
        int maxYCoord = 0;
        int enemiesFound = 0;
        for (int i = ENEMY_COUNT - 1; i >= 0; i--) {
            if (enemies[i] == NULL) {
                continue;
            }
            enemiesFound++;
            minXCoord = AlignmentUtils::getMin(minXCoord, enemies[i]->xCoord);
            maxXCoord = AlignmentUtils::getMax(maxXCoord,
                enemies[i]->xCoord + enemies[i]->getWidth());
            maxYCoord = AlignmentUtils::getMax(maxYCoord,
                enemies[i]->yCoord + enemies[i]->getHeight());

            int distance = AlignmentUtils::getAbsHorizontalDistance(enemies[i], player);
            if (distance < minDistance) {
                minDistance = distance;
                startXCoord = enemies[i]->xCoord + (enemies[i]->getWidth() / 2);
                startYCoord = enemies[i]->yCoord + enemies[i]->getHeight();
            }
        }

        if (maxYCoord >= PLAYER_Y_COORD_START) {
            StaticServiceLocator::getEventBus()->publishEvent(new Event(GROUND_REACHED));
            return;
        }
        int multiplier = 1;
        if (enemiesFound <= 4) {
            multiplier = 5 - enemiesFound;
        }

        int deltaX;
        int deltaY;
        if (minXCoord < ENEMY_LEFT_MOVING_BORDER
                || maxXCoord > ENEMY_RIGHT_MOVING_BORDER) {
            lastDirectionLeft = minXCoord < ENEMY_LEFT_MOVING_BORDER;
            deltaX = (lastDirectionLeft) ? 200 : -200;
            deltaY = 1000;
        } else if (lastDirectionLeft) {
            deltaX = 100 * multiplier;
            deltaY = 0;
        } else {
            deltaX = -100 * multiplier;
            deltaY = 0;
        }

        for (int i = 0; i < ENEMY_COUNT; i++) {
            if (enemies[i] == NULL) {
                continue;
            }
            enemies[i]->xDelta = deltaX;
            enemies[i]->yDelta = deltaY;
        }
        if (enemiesFound > 0 && AlignmentUtils::getPassedDuration(updateCount++) > 2000) {
            StaticServiceLocator::getEventBus()->publishEvent(
                new EnemyFiresBulletEvent(startXCoord, startYCoord));
            updateCount = 0;
        }
    }
};

}

#endif // ENEMIESUPDATER_H_INCLUDED
