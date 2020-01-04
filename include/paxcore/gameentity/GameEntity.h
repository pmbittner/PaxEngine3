//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_GAMEENTITY_H
#define PAXENGINE3_GAMEENTITY_H

#include <vector>

#include <polypropylene/property/Entity.h>

#include <paxutil/math/Transformation.h>
#include <polypropylene/Prefab.h>
#include <polypropylene/property/EntityManagerView.h>

#include "polypropylene/event/EventHandler.h"
#include "polypropylene/event/EventService.h"
#include "event/GameEntityParentChangedEvent.h"

#include "MotionType.h"
#include "Tag.h"

namespace PAX {
    class World;
    class WorldLayer;
    class GameEntityProperty;
    using GameEntityPrefab = Prefab<GameEntity>;

    class GameEntity : public Entity<GameEntity, GameEntityProperty> {
        friend class World;
        friend class WorldLayer;

    private:
        Transformation transform;
        // The motionType should actually be const, but it made problems with prefabs.
        MotionType motionType = MotionType::Static;
        std::vector<Tag> tags;

        GameEntity * parent = nullptr;
        std::vector<GameEntity*> children;

        WorldLayer *worldLayer = nullptr;

    public:
        EventHandler<GameEntityParentChangedEvent&> OnParentChanged;

        GameEntity();
        ~GameEntity() override;

        Transformation& getTransformation();
        void setParent(GameEntity *parent);
        PAX_NODISCARD GameEntity* getParent() const;
        PAX_NODISCARD const std::vector<GameEntity*>& getChildren() const;
        PAX_NODISCARD WorldLayer* getWorldLayer() const;

        // TODO: This should not be changeable later. Add some sort of finalisation or so.
        void i_setMotionType(MotionType motionType);
        PAX_NODISCARD MotionType getMotionType() const;

        void addTag(const Tag & tag);
        bool removeTag(const Tag & tag);
        PAX_NODISCARD bool hasTag(const Tag & tag) const;
        PAX_NODISCARD const std::vector<Tag> & getTags() const;

        PAX_NODISCARD bool isActive() const;
    };

    using GameEntityManager = EntityManager<GameEntity>;

    template<typename... RequiredProperties>
    using GameEntityManagerView = EntityManagerView<GameEntity, RequiredProperties...>;
}

#endif //PAXENGINE3_GAMEENTITY_H