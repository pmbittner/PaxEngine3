//
// Created by Paul on 02.07.2019.
//

#ifndef PAXENGINE3_TILEMAPTRANSITION_H
#define PAXENGINE3_TILEMAPTRANSITION_H

#include <paxcore/entity/EntityProperty.h>

namespace PAX {
    namespace Tiles {
        class TileMapTransition : public EntityProperty {
            PAX_PROPERTY(TileMapTransition, PAX_PROPERTY_IS_CONCRETE)
            PAX_PROPERTY_DERIVES(EntityProperty)
            PAX_PROPERTY_IS_SINGLE

            Path targetMap;
            int targetTransitionID;

        public:
            TileMapTransition(const Path & targetMap, int targetTransitionID);
        };
    }
}

#endif //PAXENGINE3_TILEMAPTRANSITION_H
