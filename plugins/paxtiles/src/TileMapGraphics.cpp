//
// Created by paul on 03.01.19.
//

#include <paxtiles/include/paxtiles/TileMapGraphics.h>

namespace PAX {
    namespace Tiles {
        PAX_PROPERTY_SOURCE(PAX::Tiles::TileMapGraphics)

        TileMapGraphics::TileMapGraphics(const TileMap& tileMap) : Super(), tilemap(tileMap), meshNode(tilemap.getMesh()) {

        }

        void TileMapGraphics::attached(PAX::Entity &entity) {
            Transformation & t = entity.getTransformation();
            t.setScale(t.getScale() * glm::vec3(tilemap.getSpriteSheet()->getCellSize(), 1));
        }

        void TileMapGraphics::detached(PAX::Entity &entity) {
            Transformation & t = entity.getTransformation();
            t.setScale(t.getScale() / glm::vec3(tilemap.getSpriteSheet()->getCellSize(), 1));
        }

        const TileMap & TileMapGraphics::getTileMap() {
            return tilemap;
        }

        void TileMapGraphics::render(PAX::RenderOptions &renderOptions) {
            Super::render(renderOptions);

            tilemap.getSpriteSheet()->getTexture()->bind();
            meshNode.render(renderOptions);
            tilemap.getSpriteSheet()->getTexture()->unbind();
        }
    }
}