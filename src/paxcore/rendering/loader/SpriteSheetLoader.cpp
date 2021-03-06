//
// Created by paul on 03.01.19.
//

#include <polypropylene/io/Path.h>
#include <paxcore/rendering/loader/SpriteSheetLoader.h>
#include <paxcore/service/Services.h>
#include "polypropylene/serialisation/json/nlohmann/Json.h"

namespace PAX {
    bool SpriteSheetLoader::canLoad(PAX::Path path, int columns, int rows) const {
        return Services::GetResources().getLoader<Texture>(path) != nullptr;
    }

    std::shared_ptr<SpriteSheet> SpriteSheetLoader::load(PAX::Path path, int columns, int rows) {
        std::shared_ptr<Texture> texture = Services::GetResources().loadOrGet<Texture>(path);
        return std::make_shared<SpriteSheet>(texture, columns, rows);
    }

    //*/
    std::shared_ptr<SpriteSheet>
    SpriteSheetLoader::loadOrGetFromJson(Resources &resources, const nlohmann::json & j) const {
        Path p      = JsonToString(j.at("Path"));
        int columns = String::convertTo<int>(JsonToString(j["Columns"]));
        int rows    = String::convertTo<int>(JsonToString(j["Rows"]));
        return resources.loadOrGet<SpriteSheet>(p, columns, rows);
    }//*/
}