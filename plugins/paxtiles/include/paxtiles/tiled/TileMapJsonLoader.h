//
// Created by Paul on 31.03.2019.
//

#ifndef PAXENGINE3_TILEMAPJSONLOADER_H
#define PAXENGINE3_TILEMAPJSONLOADER_H

#include <paxutil/resources/ResourceLoader.h>
#include "../TileMap.h"

namespace PAX {
    namespace Tiles {
        class TileMapJsonLoader : public ResourceLoader<TileMap, Path> {
        public:
            bool canLoad(Path) const override;
            std::shared_ptr<TileMap> load(Path) override;
            std::shared_ptr<TileMap> loadToOrGetFromResources(Resources &resources, const VariableHierarchy &parameters) override;
        };
    }
}

#endif //PAXENGINE3_TILEMAPJSONLOADER_H
