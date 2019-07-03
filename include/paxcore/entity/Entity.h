//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITY_H
#define PAXENGINE3_ENTITY_H

#include <vector>

#include <paxutil/property/PropertyContainer.h>

#include <paxutil/math/Transformation.h>
#include <paxutil/property/construction/PropertyContainerPrefab.h>
#include <paxutil/property/PropertyContainerManagerView.h>

#include "paxutil/event/EventHandler.h"
#include "paxutil/event/EventService.h"
#include "event/EntityParentChangedEvent.h"

namespace PAX {
    class World;
    class WorldLayer;

    using EntityPrefab = PropertyContainerPrefab<Entity>;

    class Entity : public PropertyContainer<Entity> {
        friend class World;
        friend class WorldLayer;

    private:
        Transformation transform;

        Entity * parent = nullptr;
        std::vector<Entity*> children;

        WorldLayer *worldLayer = nullptr;

        void updateActiveStatus();

    public:
        EventHandler<EntityParentChangedEvent&> OnParentChanged;

        Entity();
        ~Entity() override;

        Transformation& getTransformation();
        void setParent(Entity *parent);
        Entity* getParent() const;
        const std::vector<Entity*>& getChildren() const;
        WorldLayer* getWorldLayer() const;
    };

    using EntityManager = PropertyContainerManager<Entity>;

    template<typename... RequiredProperties>
    using EntityManagerView = PropertyContainerManagerView<Entity, RequiredProperties...>;
}

#endif //PAXENGINE3_ENTITY_H