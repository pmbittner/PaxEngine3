//
// Created by Paul on 28.09.2018.
//

#ifndef PAXENGINE3_BOX2DWORLD_H
#define PAXENGINE3_BOX2DWORLD_H

#include <paxcore/world/WorldLayerProperty.h>

namespace PAX {
    namespace Physics {
        namespace Box2D {
            class World : public WorldLayerProperty {
                PAX_PROPERTY(PAX::Physics::Box2D::World, PAX_PROPERTY_IS_CONCRETE)
                PAX_PROPERTY_DERIVES(WorldLayerProperty)
                PAX_PROPERTY_IS_SINGLE

            public:
                World();
            };
        }
    }
}

#endif //PAXENGINE3_BOX2DWORLD_H
