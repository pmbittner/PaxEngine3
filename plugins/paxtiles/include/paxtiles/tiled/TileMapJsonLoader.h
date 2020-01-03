//
// Created by Paul on 31.03.2019.
//

#ifndef PAXENGINE3_TILEMAPJSONLOADER_H
#define PAXENGINE3_TILEMAPJSONLOADER_H

#include <paxutil/resources/ResourceLoader.h>
#include <polypropylene/serialisation/json/JsonFwd.h>
#include "../TileMap.h"

namespace PAX {
    namespace Tiles {
        class TileMapJsonLoader : public ResourceLoader<TileMap, Path> {

            void loadTileLayer(
                    const nlohmann::json & layerj,
                    std::shared_ptr<TileMap> & map,
                    const std::vector<std::shared_ptr<TileSet>> & tilesets,
                    const std::vector<int> & gids);

            void loadObjectGroup(
                    const nlohmann::json & layerj,
                    std::shared_ptr<TileMap> & map,
                    const std::vector<std::shared_ptr<TileSet>> & tilesets,
                    const std::vector<int> & gids);

        public:
            bool canLoad(Path) const override;
            std::shared_ptr<TileMap> load(Path) override;
            std::shared_ptr<TileMap> loadToOrGetFromResources(Resources &resources, const VariableHierarchy &parameters) override;
        };
    }
}

#endif //PAXENGINE3_TILEMAPJSONLOADER_H
