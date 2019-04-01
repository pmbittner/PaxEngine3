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

            if (auto s = provider.get<glm::vec3>("scale")) {
                setScale(s.value());
            }
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

        TileMapProperty::TileMapProperty(const std::shared_ptr<TileMap> & tilemap) :
        tileMap(tilemap),
        scale(1),
        layerEntities(tileMap->getLayers().size())
        {
            initialize();

            int i = 0;
            for (TileMap::Layer & layer : tileMap->getLayers()) {
                auto graphics = new TileMapGraphics(layer);
                graphics->setShader(tileMapShader);
                Entity & e = layerEntities[i];
                e.add(graphics);
                e.getTransformation().z() = layer.z;
                //std::cout << layer.getMap() << " has z = " << layer.z << std::endl;
                ++i;
            }
        }

        void TileMapProperty::attached(PAX::WorldLayer & worldLayer) {
            for (Entity & e : layerEntities)
                worldLayer.spawn(&e);
        }

        void TileMapProperty::detached(PAX::WorldLayer & worldLayer) {
            for (Entity & e : layerEntities) {
                if (e.getWorldLayer() == &worldLayer) {
                    worldLayer.despawn(&e);
                }
            }
        }

        void TileMapProperty::setScale(const glm::vec3 &scale) {
            glm::vec3 delta = scale / getScale();

            for (Entity & e : layerEntities) {
                Transformation & t = e.getTransformation();
                t.setScale(t.getScale() * delta);
            }

            this->scale = scale;
        }

        const glm::vec3& TileMapProperty::getScale() const {
            return scale;
        }
    }
}