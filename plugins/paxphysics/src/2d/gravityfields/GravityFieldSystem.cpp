//
// Created by Paul Bittner on 07.02.2021.
//

#include <paxphysics/2d/gravityfields/GravityFieldSystem.h>
#include <paxphysics/2d/gravityfields/GravityFieldRegister.h>

namespace PAX::Physics {
    void GravityFieldSystem::update(UpdateOptions &options) {
        World * world = options.activeWorld;
        if (GravityFieldRegister * gravityFieldRegister = world->get<GravityFieldRegister>()) {
            WorldsGameEntityPropertiesPool<GravityFieldSensitive> sensitives(*world);
            const std::vector<GravityField*> & gravityFields = gravityFieldRegister->getGravityFields();
            GameEntity *owner;
            for (GravityFieldSensitive *s : sensitives) {
                owner = s->getOwner();
                const glm::vec2 &pos = owner->getTransformation().position2D();
                for (GravityField *gf : gravityFields) {
                    if (gf->isInside(pos)) {
                        glm::vec2 fallDir = gf->getFallingDirection(pos);
                        if (fallDir != glm::vec2(0)) {
                            owner->get<Movement2D>()->velocity += options.dt * gf->getIntensity() * glm::normalize(fallDir);
                            break; // We can only be in one gravity field
                        } else {
                            PAX_LOG(Log::Level::Error, "GravityField " << gf << " computed illegal falling direction 0!");
                        }
                    }
                }
            }
        }
    }
}