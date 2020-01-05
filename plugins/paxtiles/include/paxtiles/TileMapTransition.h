//
// Created by Paul on 02.07.2019.
//

#ifndef PAXENGINE3_TILEMAPTRANSITION_H
#define PAXENGINE3_TILEMAPTRANSITION_H

#include <paxcore/gameentity/GameEntityProperty.h>
#include <paxcore/io/event/KeyPressedEvent.h>
#include <polypropylene/io/Path.h>

namespace PAX {
    namespace Tiles {
        class TileMapTransition : public GameEntityProperty {
            PAX_PROPERTY(TileMapTransition, PAX_PROPERTY_IS_CONCRETE)
            PAX_PROPERTY_DERIVES(GameEntityProperty)
            PAX_PROPERTY_IS_SINGLE

            Path targetMap;
            int targetTransitionID;

            TileMapTransition();

        public:
            TileMapTransition(const Path & targetMap, int targetTransitionID);

            void spawned() override;
            void despawned() override;

            void onKeyDown(KeyPressedEvent & keyPressedEvent);

            PAX_NODISCARD ClassMetadata getMetadata() override;
        };
    }
}

#endif //PAXENGINE3_TILEMAPTRANSITION_H
