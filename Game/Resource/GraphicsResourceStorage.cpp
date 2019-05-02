#ifndef GRAPHICSRESOURCESTORAGE_CPP_INCLUDED
#define GRAPHICSRESOURCESTORAGE_CPP_INCLUDED

#include "Game/Resource/GraphicsResourceStorage.h"
#include "Common/StaticServiceLocator.h"

namespace Game {

    GraphicsResourceStorage::GraphicsResourceStorage() {
        graphicsObjects = new GraphicsObject*[ELEMENT_COUNT];
        graphicsObjects[SPACE_INVADER] = StaticServiceLocator::getGraphicsService(
            )->createAnimatedObjectFromFile("img/SpaceInvader.png", 22);
        graphicsObjects[PLAYER] = StaticServiceLocator::getGraphicsService(
            )->createObjectFromFile("img/Defender.png");
        graphicsObjects[EXPLOSION] = StaticServiceLocator::getGraphicsService(
            )->createAnimatedObjectFromFile("img/Explode.png", 22);
        graphicsObjects[BULLET] = StaticServiceLocator::getGraphicsService(
            )->createObjectFromFile("img/Bullet.png");
        graphicsObjects[PAUSE_MESSAGE] = StaticServiceLocator::getGraphicsService(
            )->createTextObject("PAUSE", 0xFF, 0, 0);
        graphicsObjects[LOST_MESSAGE] = StaticServiceLocator::getGraphicsService(
            )->createTextObject("LOST", 0xFF, 0, 0);
        graphicsObjects[WON_MESSAGE] = StaticServiceLocator::getGraphicsService(
            )->createTextObject("WON", 0xFF, 0, 0);
        audioObjects = new AudioObject*[SOUND_COUNT];
        audioObjects[EXPLOSION_SOUND] = StaticServiceLocator::getGraphicsService(
            )->getAudioObject("sounds/Explosion.wav");
        audioObjects[SHOT_SOUND] = StaticServiceLocator::getGraphicsService(
            )->getAudioObject("sounds/Shot.wav");
        audioObjects[FAILURE_SOUND] = StaticServiceLocator::getGraphicsService(
            )->getAudioObject("sounds/Failure.wav");
        audioObjects[SUCCESS_SOUND] = StaticServiceLocator::getGraphicsService(
            )->getAudioObject("sounds/Success.wav");
    }

    GraphicsObject *GraphicsResourceStorage::getGraphicsObject(GraphicsIdentifier identifier) {
        return graphicsObjects[identifier];
    }

    AudioObject *GraphicsResourceStorage::getAudioObject(SoundIdentifier identifier) {
        return audioObjects[identifier];
    }

}

#endif // GRAPHICSRESOURCESTORAGE_CPP_INCLUDED
