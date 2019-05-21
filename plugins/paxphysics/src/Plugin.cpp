//
// Created by Paul on 13.08.2018.
//

#include <paxcore/Engine.h>

#include "paxphysics/Plugin.h"
#include "paxphysics/Hitbox.h"
#include "paxphysics/RigidBody.h"
#include "paxphysics/box2d/Box2DRigidBody.h"
#include "paxphysics/box2d/Box2DWorld.h"

namespace PAX {
    namespace Physics {
        void Plugin::registerProperties() {
            PAX_PROPERTY_REGISTER(PAX::Physics::Hitbox)
            PAX_PROPERTY_REGISTER(PAX::Physics::RigidBody)

            PAX_PROPERTY_REGISTER(PAX::Physics::Box2D::RigidBody)
            PAX_PROPERTY_REGISTER(PAX::Physics::Box2D::World)
        }
    }
}