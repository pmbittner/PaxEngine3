//
// Created by Paul on 23.03.2019.
//

#include <paxphysics/box2d/Box2DWorld.h>

namespace PAX {
    namespace Physics {
        namespace Box2D {
            PAX_PROPERTY_SOURCE(PAX::Physics::Box2D::World, PAX_PROPERTY_IS_CONCRETE)

            World* World::createFromProvider(ContentProvider & provider) {
                return new World();
            }

            void World::initializeFromProvider(ContentProvider & provider) {
                Super::initializeFromProvider(provider);
            }

            World::World() = default;
        }
    }
}