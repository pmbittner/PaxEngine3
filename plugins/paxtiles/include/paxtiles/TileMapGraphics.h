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
            PAX_PROPERTY(TileMapGraphics)
            PAX_PROPERTY_DERIVES(Graphics)
            PAX_PROPERTY_IS_MULTIPLE

            TileMap tilemap;
            MeshNode meshNode;

        public:
            TileMapGraphics(const TileMap& tileMap);

            void attached(Entity& entity) override;
            void detached(Entity& entity) override;

            const TileMap& getTileMap();

            void render(RenderOptions &renderOptions) override;
        };
    }
}

#endif //PAXENGINE3_TILEMAPGRAPHICS_H
