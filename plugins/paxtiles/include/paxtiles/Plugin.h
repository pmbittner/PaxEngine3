//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_PAXTILESPLUGIN_PLUGIN_H
#define PAXENGINE3_PAXTILESPLUGIN_PLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>
#include "tiled/TileMapJsonLoader.h"
#include "tiled/TileSetJsonLoader.h"
#include "paxutil/resources/JsonResourceFieldWriter.h"

namespace PAX {
    namespace Tiles {
        class Plugin : public PAX::EnginePlugin {
            TileMapJsonLoader tiledMapLoader;
            TileSetJsonLoader tiledSetLoader;

            ::PAX::JsonResourceFieldWriter<::PAX::Tiles::TileMap> jsonTileMapParser;
            ::PAX::JsonResourceFieldWriter<::PAX::Tiles::TileSet> jsonTileSetParser;

        public:
            void checkDependencies(const std::vector<EnginePlugin*> & plugins) const override;
            void registerResourceLoaders(PAX::Resources &resources) override;
            void registerJsonWriters(::PAX::Json::JsonFieldWriterRegister & writerRegister) override;
            void registerProperties() override;
        };
    }
}

#endif //PAXENGINE3_PAXTILESPLUGIN_PLUGIN_H
