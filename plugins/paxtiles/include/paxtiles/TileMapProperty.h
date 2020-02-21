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
            PAX_PROPERTY(PAX::Tiles::TileMapProperty, PAX_PROPERTY_IS_CONCRETE)
            PAX_PROPERTY_DERIVES(PAX::WorldLayerProperty)
            PAX_PROPERTY_IS_MULTIPLE

            std::shared_ptr<TileMap> tileMap;
            std::vector<GameEntity> layerEntities;
            glm::vec3 scale = glm::vec3(1);

            static std::shared_ptr<Shader> tileMapShader;
            static void initialize();

            TileMapProperty();
            void init();

        public:
            explicit TileMapProperty(const std::shared_ptr<TileMap> & tilemap);

            void attached(WorldLayer & worldLayer) override;
            void detached(WorldLayer & worldLayer) override;

            void setScale(const glm::vec3 & scale);
            PAX_NODISCARD const glm::vec3 & getScale() const;

            PAX_NODISCARD ClassMetadata getMetadata() override;
            void created() override;
        };
    }
}

#endif //PAXENGINE3_TILEMAPPROPERTY_H
