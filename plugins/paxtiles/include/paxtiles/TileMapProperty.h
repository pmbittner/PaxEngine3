//
// Created by paul on 03.01.19.
//

#ifndef PAXENGINE3_TILEMAPPROPERTY_H
#define PAXENGINE3_TILEMAPPROPERTY_H

#include <paxcore/world/WorldLayerProperty.h>
#include "TileMap.h"

namespace PAX {
    namespace Tiles {
        class TileMapProperty : public WorldLayerProperty {
            PAX_PROPERTY_DERIVES(WorldLayerProperty)
            PAX_PROPERTY_IS_SINGLE

            Entity entity;
            static std::shared_ptr<Shader> tileMapShader;

        public:
            TileMapProperty(const TileMap & tilemap);

            static void initialize();

            void attached(WorldLayer & worldLayer) override;
            void detached(WorldLayer & worldLayer) override;

            Entity& getTileMapEntity();
        };
    }
}

#endif //PAXENGINE3_TILEMAPPROPERTY_H
