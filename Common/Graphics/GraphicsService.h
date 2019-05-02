#ifndef GRAPHICSSERVICE_H_INCLUDED
#define GRAPHICSSERVICE_H_INCLUDED

#include <string>
#include "Common/Graphics/GraphicsObject.h"
#include "Game/InputMask.hpp"
#include "Common/Audio/AudioObject.h"

namespace Game {
class GraphicsService {

public:
    virtual ~GraphicsService() {
    }
    virtual void updateInputMask(InputMask *inputMask) = 0;
    virtual GraphicsObject *createTextObject(const std::string &message, uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual GraphicsObject *createObjectFromFile(const std::string &path) = 0;
    virtual GraphicsObject *createAnimatedObjectFromFile(const std::string &path, int tileWidth) = 0;
    virtual void flipBuffer() = 0;
    virtual void delay(uint32_t delay) = 0;
    virtual void quitGame() = 0;
    virtual bool isGameRunning() = 0;
    virtual AudioObject *getAudioObject(const std::string &path) = 0;
};

}
#endif // GRAPHICSSERVICE_H_INCLUDED
