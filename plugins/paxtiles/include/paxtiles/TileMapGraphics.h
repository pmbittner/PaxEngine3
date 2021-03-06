//
// Created by paul on 03.01.19.
//

#ifndef PAXENGINE3_TILEMAPGRAPHICS_H
#define PAXENGINE3_TILEMAPGRAPHICS_H

#include <paxcore/rendering/Graphics.h>
#include <paxcore/rendering/scenegraph/nodes/MeshNode.h>
#include "TileMap.h"

namespace PAX {
    namespace Tiles {
        class TileMapGraphics : public Graphics {
            PAX_PROPERTY(::PAX::Tiles::TileMapGraphics, PAX_PROPERTY_IS_ABSTRACT)
            PAX_PROPERTY_DERIVES(::PAX::Graphics)
            PAX_PROPERTY_IS_MULTIPLE

            TileMap::Layer & tileLayer;

        public:
            explicit TileMapGraphics(TileMap::Layer & tileLayer);

            void attached(GameEntity& entity) override;
            void detached(GameEntity& entity) override;

            void render(RenderOptions &renderOptions) override;
        };
    }
}

#endif //PAXENGINE3_TILEMAPGRAPHICS_H
