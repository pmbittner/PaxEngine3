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
            PAX_NODISCARD bool canLoad(Path) const override;
            PAX_NODISCARD std::shared_ptr<TileSet> load(Path) override;
            PAX_NODISCARD std::shared_ptr<TileSet> loadOrGetFromJson(Resources &resources, const nlohmann::json & j) const override;
        };
    }
}

#endif //PAXENGINE3_TILESETJSONLOADER_H
