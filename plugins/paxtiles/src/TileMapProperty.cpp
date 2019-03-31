//
// Created by paul on 03.01.19.
//

#include "paxtiles/TileMapProperty.h"
#include "paxtiles/TileMapGraphics.h"

namespace PAX {
    namespace Tiles {
        PAX_PROPERTY_SOURCE(PAX::Tiles::TileMapProperty, PAX_PROPERTY_IS_CONCRETE)

        TileMapProperty * TileMapProperty::createFromProvider(ContentProvider & provider) {
            return new TileMapProperty(provider.requireResource<TileMap>("map"));
        }

        void TileMapProperty::initializeFromProvider(ContentProvider & provider) {
            Super::initializeFromProvider(provider);
        }

        std::shared_ptr<Shader> TileMapProperty::tileMapShader = nullptr;

        void TileMapProperty::initialize() {
            if (tileMapShader == nullptr) {
                tileMapShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getResourcePath() + "/shader/tilemap/tilemap.vert",
                                Services::GetPaths().getResourcePath() + "/shader/tilemap/tilemap.frag"
                        )
                );
            }
        }

        TileMapProperty::TileMapProperty(const std::shared_ptr<TileMap> & tilemap) : tileMap(tilemap) {
            for (const TileMap::Layer & layer : tileMap->getLayers()) {
                auto graphics = new TileMapGraphics(tilemap);
                graphics->setShader(tileMapShader);
                layerEntities.emplace_back();
                Entity & e = layerEntities.back();
                e.add(graphics);
                e.getTransformation().z() = layer.z;
            }
        }

        void TileMapProperty::attached(PAX::WorldLayer &worldLayer) {
            for (Entity & e : layerEntities)
                worldLayer.spawn(&e);
        }

        void TileMapProperty::detached(PAX::WorldLayer &worldLayer) {
            for (Entity & e : layerEntities)
                worldLayer.despawn(&e);
        }
    }
}