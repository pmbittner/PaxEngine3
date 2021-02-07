//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/material/PhysicsMaterial.h>

namespace PAX::Physics {
    const std::shared_ptr<PhysicsMaterial> & PhysicsMaterial::GetDefaultMaterial() {
        static std::shared_ptr<PhysicsMaterial> mat
            = std::make_shared<PhysicsMaterial>(1.f, 1.f, 0.f);
        return mat;
    }

    PhysicsMaterial::PhysicsMaterial(float density, float friction, float elasticity)
    : density(density), friction(friction), elasticity(elasticity)
    {

    }
}