//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_SCENEGRAPHBUILDER_H
#define PAXENGINE3_SCENEGRAPHBUILDER_H

#include "../Graphics.h"
#include "../../world/event/EntitySpawnedEvent.h"
#include "../../world/event/EntityDespawnedEvent.h"
#include "../../event/EventListener.h"

namespace PAX {
    class SceneGraphBuilder : public EventListener<EntitySpawnedEvent>, public EventListener<EntityDespawnedEvent> {
    public:
        void initialize();

        virtual void onEvent(EntitySpawnedEvent* e) override;
        virtual void onEvent(EntityDespawnedEvent* e) override;

        void addGraphics(Graphics *g);
        void removeGraphics(Graphics *g);
    };
}

#endif //PAXENGINE3_SCENEGRAPHBUILDER_H
