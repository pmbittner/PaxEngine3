//
// Created by paul on 03.01.19.
//

#ifndef PAXENGINE3_TILEMAP_H
#define PAXENGINE3_TILEMAP_H

#include <paxcore/rendering/data/Mesh.h>
#include <paxcore/rendering/data/SpriteSheet.h>
#include <paxcore/rendering/scenegraph/nodes/MeshNode.h>
#include <paxcore/gameentity/GameEntityIDService.h>

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
                TileMap * map = nullptr;

                void finalize(const std::vector<std::shared_ptr<TileSet>> & tileSets);
                bool isFinalized() const;

            public:
                int x = 0, y = 0, z = 0;
                int width, height;
                float opacity = 1;
                std::string name = "<unknown>";

                Layer(const std::vector<Tile> & tiles, int width);

                void render(RenderOptions &renderOptions) override;

                TileMap* getMap();

                Tile & getTileAt(int x, int y);
            };

        private:
            std::vector<Layer> layers;
            std::vector<std::shared_ptr<TileSet>> tileSets;
            std::vector<std::pair<GameEntity*, GameEntityID>> entities;

            glm::ivec2 tileSize;
            glm::ivec2 mapSize;

        public:
            explicit TileMap(
                    const std::vector<std::shared_ptr<TileSet>> & tileSets,
                    int width,
                    int height,
                    int tilewidth,
                    int tileheight);

            Layer & addLayer(const std::vector<Tile> & tiles, int width);

            std::vector<Layer> & getLayers();
            const std::vector<std::pair<GameEntity*, GameEntityID>> & getEntities() const;
            const std::vector<std::shared_ptr<TileSet>> & getTileSets();
            const glm::ivec2 & getTileSize() const;
            const glm::ivec2 & getSizeInTiles() const;

            // TODO: This should be private.
            void _addGameEntity(GameEntity* entity, GameEntityID id = GameEntityIDService::InvalidID);
        };
    }
}

#endif //PAXENGINE3_TILEMAP_H
