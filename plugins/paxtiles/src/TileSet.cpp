//
// Created by Paul on 31.03.2019.
//

#include <paxtiles/TileSet.h>
#include <polypropylene/log/Assert.h>

namespace PAX {
    namespace Tiles {
        TileSet::TileSet(const std::shared_ptr<PAX::Texture> &texture, int columns, int rows, TileInfo * tileInfo)
        :
        spriteSheet(texture, columns, rows),
        info(tileInfo),
        tileSize(texture->getWidth() / columns, texture->getHeight() / rows)
        {

        }

        TileSet::~TileSet() {
            delete[] info;
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

        TileInfo & TileSet::getTileInfo(int columnIndex, int rowIndex) const {
            const glm::ivec2 & size = spriteSheet.getDimensions();
            PAX_ASSERT(0 <= columnIndex && columnIndex < size.x);
            PAX_ASSERT(0 <= rowIndex && rowIndex < size.y);

            return info[rowIndex * size.x + columnIndex];
        }

        TileInfo & TileSet::getTileInfo(int index) const {
            const glm::ivec2 & size = spriteSheet.getDimensions();
            PAX_ASSERT(0 <= index && index < size.x * size.y);
            return info[index];
        }

        const glm::ivec2 & TileSet::getTileSize() const {
            return tileSize;
        }
    }
}