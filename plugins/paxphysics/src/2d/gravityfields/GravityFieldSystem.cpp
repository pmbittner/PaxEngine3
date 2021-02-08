//
// Created by Paul Bittner on 07.02.2021.
//

#include <paxphysics/2d/gravityfields/GravityFieldSystem.h>
#include <paxphysics/2d/gravityfields/GravityFieldRegister.h>

namespace PAX::Physics {
    void GravityFieldSystem::update(UpdateOptions &options) {
        if (GravityFieldRegister * gravityFieldRegister = options.activeWorld->get<GravityFieldRegister>()) {
            const std::vector<GravityField*> & gravityFields = gravityFieldRegister->getGravityFields();
            GameEntity *owner;
            for (GravityFieldSensitive *s : sensitives) {
                owner = s->getOwner();
                const glm::vec2 &pos = owner->getTransformation().position2D();
                for (GravityField *gf : gravityFields) {
                    if (gf->isInside(pos)) {
                        // TODO: Only move when not blocked / grounded
                        owner->get<Movement2D>()->velocity += options.dt * gf->getIntensity() * gf->getFallingDirection(pos);
                        break;
                    }
                }
            }
        }
    }
}