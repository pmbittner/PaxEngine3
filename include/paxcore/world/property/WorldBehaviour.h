//
// Created by Paul on 24.03.2019.
//

#ifndef PAXENGINE3_WORLDBEHAVIOUR_H
#define PAXENGINE3_WORLDBEHAVIOUR_H

#include <paxcore/world/WorldProperty.h>
#include <paxcore/function/Updateable.h>

namespace PAX {
    class WorldBehaviour : public WorldProperty, public Updateable {
        PAX_PROPERTY(PAX::WorldBehaviour, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(PAX::WorldProperty)
        PAX_PROPERTY_IS_MULTIPLE
    };
}

#endif //PAXENGINE3_WORLDBEHAVIOUR_H
