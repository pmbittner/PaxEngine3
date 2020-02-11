//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_PAXTILESPLUGIN_PLUGIN_H
#define PAXENGINE3_PAXTILESPLUGIN_PLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>
#include "tiled/TileMapJsonLoader.h"
#include "tiled/TileSetJsonLoader.h"
#include "paxutil/resources/JsonResourceParser.h"

namespace PAX {
    namespace Tiles {
        class Plugin : public PAX::EnginePlugin {
            TileMapJsonLoader tiledMapLoader;
            TileSetJsonLoader tiledSetLoader;

            ::PAX::JsonResourceParser<::PAX::Tiles::TileMap> jsonTileMapParser;
            ::PAX::JsonResourceParser<::PAX::Tiles::TileSet> jsonTileSetParser;

        public:
            void registerResourceLoaders(PAX::Resources &resources) override;
            void registerJsonParsers(::PAX::Json::JsonParserRegister & parserRegister) override;
            void registerProperties() override;
        };
    }
}

#endif //PAXENGINE3_PAXTILESPLUGIN_PLUGIN_H
