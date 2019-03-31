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
            PAX_PROPERTY(TileMapProperty, PAX_PROPERTY_IS_CONCRETE)
            PAX_PROPERTY_DERIVES(WorldLayerProperty)
            PAX_PROPERTY_IS_MULTIPLE

            std::shared_ptr<TileMap> tileMap;
            std::vector<Entity> layerEntities;
            static std::shared_ptr<Shader> tileMapShader;

        public:
            explicit TileMapProperty(const std::shared_ptr<TileMap> & tilemap);

            static void initialize();

            void attached(WorldLayer & worldLayer) override;
            void detached(WorldLayer & worldLayer) override;
        };
    }
}

#endif //PAXENGINE3_TILEMAPPROPERTY_H
