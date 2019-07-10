//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_PAXTILESPLUGIN_PLUGIN_H
#define PAXENGINE3_PAXTILESPLUGIN_PLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>
#include "tiled/TileMapJsonLoader.h"
#include "tiled/TileSetJsonLoader.h"

namespace PAX {
    namespace Tiles {
        class Plugin : public PAX::EnginePlugin {
            TileMapJsonLoader tiledMapLoader;
            TileSetJsonLoader tiledSetLoader;

        public:
            void registerResourceLoaders(PAX::Resources &resources) override;
            void registerProperties() override;
        };
    }
}

#endif //PAXENGINE3_PAXTILESPLUGIN_PLUGIN_H
