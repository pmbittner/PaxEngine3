//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENT_H
#define PAXENGINE3_ENTITYCOMPONENT_H

#include <polypropylene/property/Property.h>

namespace PAX {
    class GameEntity;

    class GameEntityProperty : public Property<GameEntity> {
        PAX_PROPERTY(GameEntityProperty, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(Property<GameEntity>)
        PAX_PROPERTY_IS_MULTIPLE

    public:
        virtual void spawned();
        virtual void despawned();
    };
}

#include "GameEntity.h"

#endif //PAXENGINE3_ENTITYCOMPONENT_H
