//
// Created by paul on 03.01.19.
//

#include "paxtiles/TileMapGraphics.h"

namespace PAX {
    namespace Tiles {
        PAX_PROPERTY_INIT(::PAX::Tiles::TileMapGraphics) {}

        TileMapGraphics::TileMapGraphics(TileMap::Layer & tileLayer) : Super(), tileLayer(tileLayer) {
            init();
        }

        void TileMapGraphics::attached(PAX::GameEntity &entity) {
            Transformation & t = entity.getTransformation();
            t.setScale(t.getScale() * glm::vec3(tileLayer.getMap()->getTileSize(), 1));
        }

        void TileMapGraphics::detached(PAX::GameEntity &entity) {
            Transformation & t = entity.getTransformation();
            t.setScale(t.getScale() / glm::vec3(tileLayer.getMap()->getTileSize(), 1));
        }

        void TileMapGraphics::render(PAX::RenderOptions &renderOptions) {
            //std::cout << "TileMapGraphics::render" << std::endl;
            Super::render(renderOptions);
            const std::vector<std::shared_ptr<TileSet>> & tileSets = tileLayer.getMap()->getTileSets();

            for (const std::shared_ptr<TileSet> & tileSet : tileSets) {
                tileSet->getSpriteSheet().getTexture()->bind();
            }

            tileLayer.render(renderOptions);

            for (auto it = tileSets.rbegin(); it != tileSets.rend(); ++it) {
                (*it)->getSpriteSheet().getTexture()->unbind();
            }
        }
    }
}