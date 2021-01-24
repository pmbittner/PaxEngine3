//
// Created by Paul on 31.03.2019.
//

#ifndef PAXENGINE3_TILEMAPJSONLOADER_H
#define PAXENGINE3_TILEMAPJSONLOADER_H

#include <paxutil/resources/ResourceLoader.h>
#include <polypropylene/serialisation/json/nlohmann/JsonFwd.h>
#include "../TileMap.h"

namespace PAX {
    namespace Tiles {
        /**
         * Loads a TileMap from a path pointing to a json file.
         * The json file has to be created with the Tiled Map Editor (mapeditor.org).
         * Tiled supports custom values.
         * We currently use:
         * for TileMaps:
         * - An objectgroup layer with the name "Main" will be considered as the central layer.
         *   It will get z=0 and all other layers are shifted accordingly.
         *   That way, you can safely place your entities at any z value between -1 and 1.
         * - The "type" of objects in an objectgroup layer is interpreted as a path to a prefab file from
         *   which that object can be constructed.
         * for TileSets:
         * - Any tile with the custom boolean property "solid" set to true, will be considered solid by
         *   the physics system. It will get a quadratic hitbox fitting that tile.
         */
        class TileMapJsonLoader : public ResourceLoader<TileMap, Path> {
            void loadTileLayer(
                    const nlohmann::json & layerj,
                    std::shared_ptr<TileMap> & map,
                    const std::vector<std::shared_ptr<TileSet>> & tilesets,
                    const std::vector<int> & gids,
                    const int z);

            void loadObjectGroup(
                    const nlohmann::json & layerj,
                    std::shared_ptr<TileMap> & map,
                    const std::vector<std::shared_ptr<TileSet>> & tilesets,
                    const std::vector<int> & gids,
                    const int z);

        public:
            PAX_NODISCARD bool canLoad(Path) const override;
            PAX_NODISCARD std::shared_ptr<TileMap> load(Path) override;
            PAX_NODISCARD std::shared_ptr<TileMap> loadOrGetFromJson(Resources &resources, const nlohmann::json & j) const override;
        };
    }
}

#endif //PAXENGINE3_TILEMAPJSONLOADER_H
