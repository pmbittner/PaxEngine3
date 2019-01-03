//
// Created by paul on 03.01.19.
//

#include <paxtiles/TileMapProperty.h>
#include <paxtiles/include/paxtiles/TileMapGraphics.h>

namespace PAX {
    namespace Tiles {
        std::shared_ptr<Shader> TileMapProperty::tileMapShader = nullptr;

        void TileMapProperty::initialize() {
            tileMapShader = Services::GetResources().loadOrGet<Shader>(
                    Shader::FileInfo(
                            Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.vert",
                            Services::GetPaths().getResourcePath() + "/shader/sprite/sprite.frag"
                            )
                    );
        }

        TileMapProperty::TileMapProperty(const TileMap & tilemap) {
            auto graphics = Services::GetDefaultAllocationService().create<TileMapGraphics>(tilemap);
            graphics->setShader(tileMapShader);
            entity.add(graphics);
        }

        void TileMapProperty::attached(PAX::WorldLayer &worldLayer) {
            worldLayer.spawn(&entity);
        }

        void TileMapProperty::detached(PAX::WorldLayer &worldLayer) {
            worldLayer.despawn(&entity);
        }

        Entity& TileMapProperty::getTileMapEntity() {
            return entity;
        }
    }
}