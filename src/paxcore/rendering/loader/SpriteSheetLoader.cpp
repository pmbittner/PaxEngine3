//
// Created by paul on 03.01.19.
//

#include <paxutil/io/Path.h>
#include <paxcore/rendering/loader/SpriteSheetLoader.h>
#include <paxcore/service/Services.h>

namespace PAX {
    bool SpriteSheetLoader::canLoad(PAX::Path path, int columns, int rows) const {
        return Services::GetResources().getLoader<Texture>(path) != nullptr;
    }

    std::shared_ptr<SpriteSheet> SpriteSheetLoader::load(PAX::Path path, int columns, int rows) {
        std::shared_ptr<Texture> texture = Services::GetResources().loadOrGet<Texture>(path);
        return std::make_shared<SpriteSheet>(texture, columns, rows);
    }

    std::shared_ptr<SpriteSheet>
    SpriteSheetLoader::loadToOrGetFromResources(Resources &resources, const VariableHierarchy &parameters) {
        Path p      = parameters.tryGet("Path");
        int columns = String::tryParse<int>(parameters.tryGet("Columns"));
        int rows    = String::tryParse<int>(parameters.tryGet("Rows"));
        return resources.loadOrGet<SpriteSheet>(p, columns, rows);
    }
}