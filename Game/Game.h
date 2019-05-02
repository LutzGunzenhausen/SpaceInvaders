#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "Game/State/MenuState.hpp"
#include "Game/InputMask.hpp"

namespace Game {

class Game {
private:
    InputMask *inputMask = NULL;
    GameState *gameState = NULL;
    GameState *nextState = NULL;
    void mainLoop();
    void updateGameState();
    void readInput();
    void update();
    void paint();
    void paintOnScreen();
public:
    Game();
    ~Game();
};

}


#endif // GAME_H_INCLUDED
