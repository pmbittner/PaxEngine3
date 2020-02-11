//
// Created by Paul on 13.08.2018.
//

#include "paxtiles/Plugin.h"

#include <paxutil/resources/Resources.h>
#include <paxtiles/TileMap.h>
#include <paxtiles/tiled/TileMapJsonLoader.h>
#include <paxtiles/tiled/TileSetJsonLoader.h>
#include <paxtiles/TileMapProperty.h>
#include <paxtiles/TileMapTransition.h>

#include <paxtiles/topdown/CharacterOrientation.h>
#include <paxtiles/topdown/CharacterSpriteAnimation.h>
#include <paxtiles/topdown/SimpleCharacterKeyboardControls.h>

namespace PAX {
    namespace Tiles {
        void Plugin::registerResourceLoaders(PAX::Resources & resources) {
            resources.registerLoader<TileMap>(&tiledMapLoader);
            resources.registerLoader<TileSet>(&tiledSetLoader);
        }

        void Plugin::registerJsonParsers(Json::JsonParserRegister & parserRegister) {
            jsonTileMapParser.registerAt(parserRegister);
            jsonTileSetParser.registerAt(parserRegister);
        }

        void Plugin::registerProperties() {
            PAX_PROPERTY_REGISTER(PAX::Tiles::TileMapProperty);

            PAX_PROPERTY_REGISTER(PAX::Tiles::CharacterOrientation);
            PAX_PROPERTY_REGISTER(PAX::Tiles::CharacterSpriteAnimation);
            PAX_PROPERTY_REGISTER(PAX::Tiles::SimpleCharacterKeyboardControls);

            PAX_PROPERTY_REGISTER(PAX::Tiles::TileMapTransition);
        }
    }
}