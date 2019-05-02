#ifndef GRAPHICSRESOURCESTORAGE_H_INCLUDED
#define GRAPHICSRESOURCESTORAGE_H_INCLUDED

#include "Common/Graphics/GraphicsObject.h"
#include "Common/Audio/AudioObject.h"
#define LOG_MESSAGE(x) StaticServiceLocator::getLoggingService()->log(x);
namespace Game {
enum GraphicsIdentifier {
    SPACE_INVADER,
    PLAYER,
    EXPLOSION,
    BULLET,
    PAUSE_MESSAGE,
    LOST_MESSAGE,
    WON_MESSAGE,
    ELEMENT_COUNT
};

enum SoundIdentifier {
    EXPLOSION_SOUND,
    SHOT_SOUND,
    FAILURE_SOUND,
    SUCCESS_SOUND,
    SOUND_COUNT
};

class GraphicsResourceStorage {
private:
    GraphicsObject **graphicsObjects;
    AudioObject **audioObjects;
public:
    GraphicsResourceStorage();
    GraphicsObject *getGraphicsObject(GraphicsIdentifier identifier);
    AudioObject *getAudioObject(SoundIdentifier identifier);
};

}


#endif // GRAPHICSRESOURCESTORAGE_H_INCLUDED
