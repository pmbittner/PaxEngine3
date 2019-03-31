//
// Created by paul on 03.01.19.
//

#include "paxtiles/TileMapGraphics.h"

namespace PAX {
    namespace Tiles {
        PAX_PROPERTY_SOURCE(::PAX::Tiles::TileMapGraphics, PAX_PROPERTY_IS_ABSTRACT)

        /*
        TileMapGraphics * TileMapGraphics::createFromProvider(ContentProvider & provider) {
            return;//new TileMapGraphics(provider.requireResource<TileMap>("map"));
        }*/


        void TileMapGraphics::initializeFromProvider(ContentProvider & provider) {
            Super::initializeFromProvider(provider);
        }//*/

        TileMapGraphics::TileMapGraphics(TileMap::Layer & tileLayer) : Super(), tileLayer(tileLayer) {

        }

        void TileMapGraphics::attached(PAX::Entity &entity) {
            Transformation & t = entity.getTransformation();
            t.setScale(t.getScale() * glm::vec3(5 * tileLayer.getMap()->getTileSize(), 1));
        }

        void TileMapGraphics::detached(PAX::Entity &entity) {
            Transformation & t = entity.getTransformation();
            t.setScale(t.getScale() / glm::vec3(5 * tileLayer.getMap()->getTileSize(), 1));
        }

        void TileMapGraphics::render(PAX::RenderOptions &renderOptions) {
            //std::cout << "TileMapGraphics::render" << std::endl;
            Super::render(renderOptions);
            tileLayer.render(renderOptions);
        }
    }
}