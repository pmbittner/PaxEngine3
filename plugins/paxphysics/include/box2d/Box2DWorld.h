//
// Created by Paul on 28.09.2018.
//

#ifndef PAXENGINE3_BOX2DWORLD_H
#define PAXENGINE3_BOX2DWORLD_H

#include <paxcore/world/WorldLayerProperty.h>

namespace PAX {
    namespace Physics {
        namespace Box2D {
            class World : public Property<PAX::WorldLayer> {
                PAX_WORLDLAYERPROPERTY_BODY(Property<PAX::WorldLayer>, false)
            public:
            };
        }
    }
}

#endif //PAXENGINE3_BOX2DWORLD_H
