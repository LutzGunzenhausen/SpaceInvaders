#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

const int FRAMES_PER_SECOND = 60;
const int DELAY_TIME = 1000 / FRAMES_PER_SECOND;
const int WINDOW_HEIGHT = 480;
const int WINDOW_WIDTH = 640;

const int ENEMY_ROW_COUNT = 4;
const int ENEMY_COLUMN_COUNT = 10;
const int ENEMY_COUNT = ENEMY_COLUMN_COUNT * ENEMY_ROW_COUNT;

const int PLAYER_X_COORD_START = WINDOW_WIDTH / 2;
const int PLAYER_Y_COORD_START = WINDOW_HEIGHT - 50;

const int ENEMY_VERTICAL_GAP = 20;
const int ENEMY_HORIZONTAL_GAP = 20;
const int ENEMY_START_X = 40;
const int ENEMY_START_Y = 20;
const int ENEMY_LEFT_MOVING_BORDER = 30;
const int ENEMY_RIGHT_MOVING_BORDER = WINDOW_WIDTH - ENEMY_LEFT_MOVING_BORDER;

// needs 3 seconds to move from side to side
const int PLAYER_X_SPEED = WINDOW_WIDTH / 3;
const int BULLET_SPEED = WINDOW_HEIGHT / -1;

enum EventTypes {
    PLAYER_FIRES_BULLET,
    ENEMY_FIRES_BULLET,
    ENTITY_DEAD,
    GROUND_REACHED
};

#endif // CONSTANTS_H_INCLUDED