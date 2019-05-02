#ifndef STATICINITIALIZER_HPP_INCLUDED
#define STATICINITIALIZER_HPP_INCLUDED

#include "Common/StaticServiceLocator.h"
#include "Common/Logging/NullLoggingService.hpp"
#include "Common/Graphics/SDLGraphicsService.hpp"
#include "Common/Physics/DefaultPhysicsService.hpp"
#include "Game/Resource/GraphicsResourceStorage.h"
namespace Game {

LoggingService *StaticServiceLocator::loggingService;
GraphicsService *StaticServiceLocator::graphicsService;
PhysicsService *StaticServiceLocator::physicsService;
EventBus *StaticServiceLocator::eventBus;
GraphicsResourceStorage *StaticServiceLocator::storage;


class StaticInitializer {
public:
    static void initialize() {
        StaticServiceLocator::setLoggingService(new NullLoggingService());
        StaticServiceLocator::setGraphicsService(new SDLGraphicsService());
        StaticServiceLocator::setPhysicsService(new DefaultPhysicsService());
        StaticServiceLocator::setEventBus(new EventBus());
        StaticServiceLocator::setGraphisResourceStorage(new GraphicsResourceStorage());
    }
};
}

#endif // STATICINITIALIZER_HPP_INCLUDED
