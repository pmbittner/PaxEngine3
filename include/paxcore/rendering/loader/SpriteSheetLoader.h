//
// Created by paul on 03.01.19.
//

#ifndef PAXENGINE3_SPRITESHEETLOADER_H
#define PAXENGINE3_SPRITESHEETLOADER_H

#include <paxcore/rendering/data/SpriteSheet.h>
#include <paxutil/resources/ResourceLoader.h>

namespace PAX {
    class SpriteSheetLoader : public ResourceLoader<SpriteSheet, Path, int, int> {
    public:
        std::shared_ptr<SpriteSheet> loadOrGetFromJson(Resources & resources, const nlohmann::json & json) const override;
        PAX_NODISCARD bool canLoad(Path, int, int) const override;
        PAX_NODISCARD std::shared_ptr<SpriteSheet> load(Path, int, int) override;
    };
}

#endif //PAXENGINE3_SPRITESHEETLOADER_H
