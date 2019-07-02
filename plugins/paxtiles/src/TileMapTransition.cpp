//
// Created by Paul on 02.07.2019.
//

#include <paxtiles/TileMapTransition.h>

namespace PAX {
    namespace Tiles {
        PAX_PROPERTY_SOURCE(TileMapTransition, PAX_PROPERTY_IS_CONCRETE)

        TileMapTransition::This * TileMapTransition::createFromProvider(PAX::ContentProvider & c) {
            return new TileMapTransition(c.require<Path>("transition_target_map"), c.require<int>("transition_target_id"));
        }

        void TileMapTransition::initializeFromProvider(PAX::ContentProvider & c) {
            Super::initializeFromProvider(c);
        }

        TileMapTransition::TileMapTransition(const PAX::Path &targetMap, int targetTransitionID)
        : targetMap(targetMap), targetTransitionID(targetTransitionID)
        {
            PAX_PRINT_OUT("Created with targetMap = " << targetMap << " and targetID = " << targetTransitionID)
        }
    }
}