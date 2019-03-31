//
// Created by paul on 03.01.19.
//

#include "paxtiles/TileMapGraphics.h"

namespace PAX {
    namespace Tiles {
        PAX_PROPERTY_SOURCE(PAX::Tiles::TileMapGraphics, PAX_PROPERTY_IS_CONCRETE)

        TileMapGraphics * TileMapGraphics::createFromProvider(ContentProvider & provider) {
            return new TileMapGraphics(provider.requireResource<TileMap>("map"));
        }

        void TileMapGraphics::initializeFromProvider(ContentProvider & provider) {
            Super::initializeFromProvider(provider);
        }

        TileMapGraphics::TileMapGraphics(const std::shared_ptr<TileMap>& tileMap) : Super(), tilemap(tileMap) {

        }

        void TileMapGraphics::attached(PAX::Entity &entity) {
            Transformation & t = entity.getTransformation();
            t.setScale(t.getScale() * glm::vec3(tilemap->getTileSize(), 1));
        }

        void TileMapGraphics::detached(PAX::Entity &entity) {
            Transformation & t = entity.getTransformation();
            t.setScale(t.getScale() / glm::vec3(tilemap->getTileSize(), 1));
        }

        const std::shared_ptr<TileMap> & TileMapGraphics::getTileMap() {
            return tilemap;
        }

        void TileMapGraphics::render(PAX::RenderOptions &renderOptions) {
            Super::render(renderOptions);

            for (TileMap::Layer & layer : tilemap->getLayers()) {
                layer.render(renderOptions);
            }
        }
    }
}