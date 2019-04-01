//
// Created by Paul on 13.08.2018.
//

#include "paxtiles/Plugin.h"

#include <paxutil/resources/Resources.h>
#include <paxtiles/TileMap.h>
#include <paxtiles/tiled/TileMapJsonLoader.h>
#include <paxtiles/tiled/TileSetJsonLoader.h>
#include <paxtiles/TileMapProperty.h>

namespace PAX {
    namespace Tiles {
        void Plugin::registerResourceLoaders(PAX::Resources & resources) {
            resources.registerLoader<TileMap>(&tiledMapLoader);
            resources.registerLoader<TileSet>(&tiledSetLoader);
        }

        void Plugin::exp_registerProperties() {
            PropertyFactoryRegister<WorldLayer>::registerFactory<Tiles::TileMapProperty>("PAX::Tiles::TileMapProperty");
        }
    }
}