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

#include "MotionType.h"

namespace PAX {
    class World;
    class WorldLayer;

    using EntityPrefab = PropertyContainerPrefab<Entity>;

    class Entity : public PropertyContainer<Entity> {
        friend class World;
        friend class WorldLayer;

    private:
        Transformation transform;
        // The motionType should be actually const, but it made problems with prefabs.
        MotionType motionType = MotionType::Static;

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
        [[nodiscard]] Entity* getParent() const;
        [[nodiscard]] const std::vector<Entity*>& getChildren() const;
        [[nodiscard]] WorldLayer* getWorldLayer() const;

        // TODO: This should not be changeable later. Hence, add some sort of finalisation or so.
        void i_setMotionType(MotionType motionType);
        [[nodiscard]] MotionType getMotionType() const;
    };

    using EntityManager = PropertyContainerManager<Entity>;

    template<typename... RequiredProperties>
    using EntityManagerView = PropertyContainerManagerView<Entity, RequiredProperties...>;
}

#endif //PAXENGINE3_ENTITY_H