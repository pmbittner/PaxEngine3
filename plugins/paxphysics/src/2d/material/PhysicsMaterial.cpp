//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/material/PhysicsMaterial.h>

namespace PAX::Physics {
    PhysicsMaterial::PhysicsMaterial(float density, float friction, float elasticity)
    : density(density), friction(friction), elasticity(elasticity)
    {

    }
}