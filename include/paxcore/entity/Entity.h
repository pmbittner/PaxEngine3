//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITY_H
#define PAXENGINE3_ENTITY_H

#include <vector>

#include <paxutil/property/PropertyContainer.h>

#include <paxutil/math/Transformation.h>

#include "paxutil/event/EventHandler.h"
#include "paxutil/event/EventService.h"
#include "event/EntityParentChangedEvent.h"

namespace PAX {
    class World;
    class WorldLayer;

    class Entity : public PropertyContainer<Entity> {
        friend class World;
        friend class WorldLayer;

    private:
        Transformation _transform;

        //EventService _localEventService;

        Entity *_parent = nullptr;
        std::vector<Entity*> _children;

        WorldLayer *_worldLayer = nullptr;

    public:
        EventHandler<EntityParentChangedEvent&> OnParentChanged;

        Entity();
        virtual ~Entity();

        Transformation& getTransformation();
        void setParent(Entity *parent);
        Entity* getParent() const;
        const std::vector<Entity*>& getChildren() const;
        //EventService& getEventService();
        WorldLayer* getWorldLayer() const;
    };
}

#endif //PAXENGINE3_ENTITY_H