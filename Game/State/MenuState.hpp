#ifndef MENUSTATE_HPP_INCLUDED
#define MENUSTATE_HPP_INCLUDED

#include "Game/State/GameState.h"
#include "Game/State/SpaceInvadersState.hpp"
#include <iostream>

#include "Common/StaticServiceLocator.h"
#include "Common/Graphics/GraphicsService.h"
#include "Game/GameObject.hpp"
#include "Game/ObjectState/GameObjectState.h"
#include "Common/Constants.h"
#include "Common/Graphics/AlignmentUtils.h"
#define LOG_MESSAGE(x) StaticServiceLocator::getLoggingService()->log(x);

namespace Game {

struct MenuOption {
    GameObject *optionActive = NULL;
    GameObject *optionInactive = NULL;
};

enum MenuPoints {
    START,
    HIGHSCORE,
    QUIT,
    NUMBER_OF_OPTIONS
};

class MenuState : public GameState {
private:
    const int DELAY_BETWEEN_SWITCHES = 100;
    MenuOption *availableOptions = NULL;
    int selection = 0;
    int passedFrames = 0;

public:
    MenuState() {
        availableOptions = new MenuOption[NUMBER_OF_OPTIONS];
        fillInOption(availableOptions[START], "Start", 50);
        fillInOption(availableOptions[HIGHSCORE], "Highscore", 100);
        fillInOption(availableOptions[QUIT], "Quit", 150);
    }

    ~MenuState() {
        for (int i = 0; i < NUMBER_OF_OPTIONS; i++) {
            delete availableOptions[i].optionActive;
            delete availableOptions[i].optionInactive;
        }
        delete []availableOptions;
    }

    GameState* update(InputMask *inputMask) {
        passedFrames++;
        if (AlignmentUtils::getPassedDuration(passedFrames) > DELAY_BETWEEN_SWITCHES) {
            if (inputMask->isEnterActive()) {
                if (selection == 0) {
                    return new SpaceInvadersState();
                } else if (selection == 2) {
                    StaticServiceLocator::getGraphicsService()->quitGame();
                    return NULL;
                }
            } else if (inputMask->isDownActive()) {
                selection++;
                selection %= NUMBER_OF_OPTIONS;
            } else if (inputMask->isUpActive()) {
                selection--;
                if (selection < 0) {
                    selection += NUMBER_OF_OPTIONS;
                }
            }
            passedFrames = 0;
        }

        return NULL;
    }

    void paint() {
        LOG_MESSAGE("TitleState");
        for (int i = 0; i < NUMBER_OF_OPTIONS; i++) {
            if (i == selection) {
                availableOptions[i].optionActive->render();
            } else {
                availableOptions[i].optionInactive->render();
            }
        }
    }

private:
    void fillInOption(MenuOption &option, const std::string &message, int yCoord) {
        GraphicsService *graphicsService = StaticServiceLocator::getGraphicsService();

        GameObjectState *activeObject = new GameObjectState(
            graphicsService->createTextObject(message, 0xFF, 0, 0));
        int xCoord = AlignmentUtils::centerAroundCoordinate(activeObject, WINDOW_WIDTH / 2);
        option.optionActive = new GameObject(activeObject, xCoord, yCoord);
        activeObject = new GameObjectState(graphicsService->createTextObject(message, 0xFF, 0xFF, 0xFF));
        option.optionInactive = new GameObject(activeObject, xCoord, yCoord);
    }
};

}


#endif // MENUSTATE_HPP_INCLUDED
