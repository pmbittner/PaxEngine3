//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENT_H
#define PAXENGINE3_ENTITYCOMPONENT_H

#include <paxcore/OStreamOverloads.h>
#include <polypropylene/property/Property.h>

namespace PAX {
    class GameEntity;
    class World;

    class GameEntityProperty : public Property<GameEntity> {
        PAX_PROPERTY(GameEntityProperty, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(Property<GameEntity>)
        PAX_PROPERTY_IS_MULTIPLE

    public:
        virtual void spawned();
        virtual void despawned();

        PAX_NODISCARD World * getWorld() const;
    };
}

#include "GameEntity.h"

#endif //PAXENGINE3_ENTITYCOMPONENT_H
