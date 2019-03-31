//
// Created by Paul on 31.03.2019.
//

#include <paxtiles/TileSet.h>

namespace PAX {
    namespace Tiles {
        TileSet::TileSet(const std::shared_ptr<PAX::Texture> &texture, int tileWidth, int tileHeight)
        : spriteSheet(texture, tileWidth, tileHeight)
        {

        }

        const std::string & TileSet::getName() const {
            return name;
        }

        void TileSet::setName(const std::string & name) {
            this->name = name;
        }

        const SpriteSheet & TileSet::getSpriteSheet() const {
            return spriteSheet;
        }
    }
}