//
// Created by Paul on 31.03.2019.
//

#ifndef PAXENGINE3_TILESETJSONLOADER_H
#define PAXENGINE3_TILESETJSONLOADER_H

#include <paxutil/resources/ResourceLoader.h>
#include "../TileSet.h"

namespace PAX {
    namespace Tiles {
        class TileSetJsonLoader : public ResourceLoader<TileSet, Path> {
        public:
            bool canLoad(Path) const override;
            std::shared_ptr<TileSet> load(Path) override;
            std::shared_ptr<TileSet> loadToOrGetFromResources(Resources &resources, const VariableHierarchy &parameters) override;
        };
    }
}

#endif //PAXENGINE3_TILESETJSONLOADER_H
