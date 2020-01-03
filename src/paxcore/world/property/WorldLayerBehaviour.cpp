//
// Created by Bittner on 21/06/2019.
//

#include <paxcore/world/property/WorldLayerBehaviour.h>

namespace PAX {
    PAX_PROPERTY_INIT(PAX::WorldLayerBehaviour, PAX_PROPERTY_IS_ABSTRACT)

    void WorldLayerBehaviour::initializeFromProvider(PAX::ContentProvider & c) {
        Super::initializeFromProvider(c);
    }
}