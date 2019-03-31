//
// Created by paul on 03.01.19.
//

#ifndef PAXENGINE3_TILEMAP_H
#define PAXENGINE3_TILEMAP_H

#include <paxcore/rendering/data/Mesh.h>
#include <paxcore/rendering/data/SpriteSheet.h>
#include <paxcore/rendering/scenegraph/nodes/MeshNode.h>

#include "Tile.h"
#include "TileSet.h"

namespace PAX {
    namespace Tiles {
        class TileMap {
        public:
            struct Layer : public Renderable {
            private:
                friend class TileMap;
                MeshNode meshNode;
                std::vector<Tile> tiles;
                void finalize(const std::vector<std::shared_ptr<TileSet>> & tileSets);
                bool isFinalized() const;

            public:
                int x = 0, y = 0, z = 0;
                int width, height;
                float opacity = 1;
                std::string name = "<unknown>";

                Layer(const std::vector<Tile> & tiles, int width);

                void render(RenderOptions &renderOptions) override;
            };

        private:
            std::vector<Layer> layers;
            std::vector<std::shared_ptr<TileSet>> tileSets;

            glm::ivec2 tileSize;
            glm::ivec2 mapSize;

        public:
            explicit TileMap(
                    const std::vector<std::shared_ptr<TileSet>> & tileSets,
                    int width,
                    int height,
                    int tilewidth,
                    int tileheight);

            void addLayer(Layer & layer);

            // TODO: This should be const :/
            std::vector<Layer> & getLayers();
            const glm::ivec2 & getTileSize() const;
        };
    }
}

#endif //PAXENGINE3_TILEMAP_H
