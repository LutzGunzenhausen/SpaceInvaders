#ifndef STATICSERVICELOCATOR_HPP_INCLUDED
#define STATICSERVICELOCATOR_HPP_INCLUDED

#include "Common/Logging/LoggingService.h"
#include "Common/Graphics/GraphicsService.h"
#include "Common/Physics/PhysicsService.h"
#include "Game/Event/EventBus.h"
#include "Game/Resource/GraphicsResourceStorage.h"

namespace Game {

class StaticServiceLocator {
private:
    static LoggingService *loggingService;
    static GraphicsService *graphicsService;
    static PhysicsService *physicsService;
    static EventBus *eventBus;
    static GraphicsResourceStorage *storage;
public:
    static void setLoggingService(LoggingService *loggingService_) {
        loggingService = loggingService_;
    }

    static LoggingService *getLoggingService() {
        return loggingService;
    }

    static void setGraphicsService(GraphicsService *graphicsService_) {
        graphicsService = graphicsService_;
    }

    static GraphicsService *getGraphicsService() {
        return graphicsService;
    }

    static void setPhysicsService(PhysicsService *physicsService_) {
        physicsService = physicsService_;
    }

    static PhysicsService *getPhysicsService() {
        return physicsService;
    }

    static void setEventBus(EventBus *eventBus_) {
        eventBus = eventBus_;
    }

    static EventBus *getEventBus() {
        return eventBus;
    }

    static void setGraphisResourceStorage(GraphicsResourceStorage *storage_) {
        storage = storage_;
    }

    static GraphicsResourceStorage *getGraphicsResourceStorage() {
        return storage;
    }
};

}
#endif // STATICSERVICELOCATOR_HPP_INCLUDED
