#include "Game.h"
#include <chrono>
#include "Game/State/MenuState.hpp"
#include "Common/StaticServiceLocator.h"
#include "Common/Constants.h"
#define GRAPHICS StaticServiceLocator::getGraphicsService()

namespace Game {

    Game::Game() {
        gameState = new MenuState();
        inputMask = new InputMask();
        mainLoop();
    }

    void Game::mainLoop() {
        clock_t startTime;
        long elapsed;
        long waitTime;
        while (GRAPHICS->isGameRunning()) {
            startTime = clock();
            updateGameState();
            readInput();
            update();
            paint();
            paintOnScreen();
            elapsed = clock() - startTime;
            waitTime = DELAY_TIME - elapsed;
            if (waitTime < 0) {
                waitTime = 10;
            }
            GRAPHICS->delay(waitTime);
        }
    }

    void Game::updateGameState() {
        if (nextState == NULL) {
            return;
        }

        delete gameState;
        gameState = nextState;

    }

    void Game::readInput() {
        GRAPHICS->updateInputMask(inputMask);
    }

    void Game::update() {
        nextState = gameState->update(inputMask);
    }

    void Game::paint() {
        gameState->paint();
    }

    void Game::paintOnScreen() {
        GRAPHICS->flipBuffer();
    }
}
