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
#include <paxphysics/Plugin.h>

namespace PAX {
    namespace Tiles {
        void Plugin::checkDependencies(const std::vector<EnginePlugin *> &plugins) const {
            static EnginePluginTypedDependencies<Physics::Plugin> dependencies("paxtiles");
            return dependencies.checkDependencies(plugins);
        }

        void Plugin::registerResourceLoaders(PAX::Resources & resources) {
            resources.registerLoader<TileMap>(&tiledMapLoader);
            resources.registerLoader<TileSet>(&tiledSetLoader);
        }

        void Plugin::registerJsonWriters(Json::JsonFieldWriterRegister & writerRegister) {
            jsonTileMapParser.registerAt(writerRegister);
            jsonTileSetParser.registerAt(writerRegister);
        }

        void Plugin::registerProperties() {
            PAX_PROPERTY_REGISTER_AS(TileMapProperty, "TileMap");

            PAX_PROPERTY_REGISTER(CharacterOrientation);
            PAX_PROPERTY_REGISTER(CharacterSpriteAnimation);
            PAX_PROPERTY_REGISTER(SimpleCharacterKeyboardControls);

            PAX_PROPERTY_REGISTER(TileMapTransition);
        }
    }
}