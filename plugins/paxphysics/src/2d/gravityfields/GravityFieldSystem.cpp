//
// Created by Paul Bittner on 07.02.2021.
//

#include <paxphysics/2d/gravityfields/GravityFieldSystem.h>
#include <paxphysics/2d/gravityfields/GravityField.h>

namespace PAX::Physics {
    void GravityFieldSystem::update(UpdateOptions &options) {
        // todo make cache friendly
        World * world = options.activeWorld;
        const std::vector<GameEntity*> & gravityFields = world->getEntitiesWithTag(GravityField::GetTag());

        for (GravityFieldSensitive * s : sensitives) {

        }
    }
}