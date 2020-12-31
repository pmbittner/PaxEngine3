//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_GAMEENTITY_H
#define PAXENGINE3_GAMEENTITY_H

#include <vector>

#include <polypropylene/property/Entity.h>

#include <paxutil/math/Transformation.h>
#include <polypropylene/prefab/Prefab.h>
#include <polypropylene/property/EntityManagerView.h>

#include "polypropylene/event/EventHandler.h"
#include "polypropylene/event/EventService.h"
#include "event/GameEntityParentChangedEvent.h"

#include "MotionType.h"
#include "Tag.h"

#include "GameEntityProperty.h"

namespace PAX {
    class World;
    using GameEntityPrefab = Prefab<GameEntity>;

    class GameEntity final : public Entity<GameEntity, GameEntityProperty> {
        friend class World;

    private:
        Transformation transform;
        // The motionType should actually be const, but it made problems with prefabs.
        MotionType motionType = MotionType::Static;
        std::vector<Tag> tags;

        GameEntity * parent = nullptr;
        std::vector<GameEntity*> children;

        World *world = nullptr;

    protected:
        void onPropertyAdded(GameEntityProperty *property) override;
        void onPropertyRemoved(GameEntityProperty *property) override;

    public:
        EventHandler<GameEntityParentChangedEvent&> OnParentChanged;

        GameEntity();
        ~GameEntity() override;

        Transformation& getTransformation();
        void setParent(GameEntity *parent);
        PAX_NODISCARD GameEntity* getParent() const;
        PAX_NODISCARD const std::vector<GameEntity*>& getChildren() const;
        PAX_NODISCARD World* getWorld() const;

        // TODO: This should not be changeable later. Add some sort of finalisation or so.
        void i_setMotionType(MotionType motionType);
        PAX_NODISCARD MotionType getMotionType() const;

        void addTag(const Tag & tag);
        bool removeTag(const Tag & tag);
        PAX_NODISCARD bool hasTag(const Tag & tag) const;
        PAX_NODISCARD const std::vector<Tag> & getTags() const;

        void spawned();
        void despawned();
    };

    using GameEntityManager = EntityManager<GameEntity>;

    template<typename... RequiredProperties>
    using GameEntityManagerView = EntityManagerView<GameEntity, RequiredProperties...>;
}

#endif //PAXENGINE3_GAMEENTITY_H