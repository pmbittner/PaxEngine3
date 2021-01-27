//
// Created by Paul on 31.03.2019.
//

#ifndef PAXENGINE3_TILESET_H
#define PAXENGINE3_TILESET_H

#include <memory>
#include <string>
#include <paxcore/rendering/data/Texture.h>
#include <paxcore/rendering/data/SpriteSheet.h>

#include "Tile.h"

namespace PAX {
    namespace Tiles {
        class TileSet {
            SpriteSheet spriteSheet;
            std::string name = "<unknown>";
            TileInfo* info = nullptr;
            const glm::ivec2 tileSize;

        public:
            TileSet(const std::shared_ptr<Texture> & texture, int columns, int rows, TileInfo * tileInfo);
            ~TileSet();
            void setName(const std::string & name);
            const std::string & getName() const;
            const SpriteSheet & getSpriteSheet() const;
            TileInfo& getTileInfo(int columnIndex, int rowIndex) const;
            TileInfo& getTileInfo(int index) const;
            const glm::ivec2 & getTileSize() const;
        };
    }
}

#endif //PAXENGINE3_TILESET_H
