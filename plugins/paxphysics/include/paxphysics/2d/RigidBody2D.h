//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_PHYSICS_H
#define PAXENGINE3_PHYSICS_H

#include <paxcore/gameentity/GameEntityProperty.h>

namespace PAX::Physics {
    class RigidBody2D : public GameEntityProperty {
        PAX_PROPERTY(PAX::Physics::RigidBody2D, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_MULTIPLE

    public:
        RigidBody2D();
    };
}

#endif //PAXENGINE3_PHYSICS_H
