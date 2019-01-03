//
// Created by paul on 03.01.19.
//

#ifndef PAXENGINE3_TILEMAP_H
#define PAXENGINE3_TILEMAP_H

#include <paxcore/rendering/data/Mesh.h>
#include <paxcore/rendering/data/SpriteSheet.h>
#include "Tile.h"

namespace PAX {
    namespace Tiles {
        class TileMap {
            std::shared_ptr<Mesh> mesh;
            std::shared_ptr<SpriteSheet> spriteSheet;

            unsigned long columns;
            unsigned long rows;

            void createMesh(const std::vector<std::vector<Tile>> & tiles);

        public:
            TileMap();

            void create(const std::vector<std::vector<Tile>> & tiles, const std::shared_ptr<SpriteSheet> & spriteSheet);

            const std::shared_ptr<Mesh> & getMesh() const;
            const std::shared_ptr<SpriteSheet> getSpriteSheet() const;

            unsigned long getColumns() const;
            unsigned long getRows() const;
        };
    }
}

#endif //PAXENGINE3_TILEMAP_H
