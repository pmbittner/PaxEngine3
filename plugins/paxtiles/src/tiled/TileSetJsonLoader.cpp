//
// Created by Paul on 31.03.2019.
//

#include <paxtiles/tiled/TileSetJsonLoader.h>
#include <paxcore/service/Services.h>
#include <paxutil/json/Json.h>
#include <paxcore/rendering/data/Texture.h>

namespace PAX {
    namespace Tiles {
        bool TileSetJsonLoader::canLoad(PAX::Path path) const {
            return Services::GetResources().getLoader<nlohmann::json>(path) != nullptr;
        }

        std::shared_ptr<TileSet> TileSetJsonLoader::load(PAX::Path path) {
            std::shared_ptr<nlohmann::json> jptr = Services::GetResources().loadOrGet<nlohmann::json>(path);
            PAX_assertNotNull(jptr, "[TileSetJsonLoader::load] TileSet json file " << path << " could not be loaded!")
            const nlohmann::json & j = *jptr.get();

            const std::string & name = j["name"];
            std::shared_ptr<Texture> image;
            {
                Path imagePath = path.getDirectory() + j["image"];
                image = Services::GetResources().loadOrGet<Texture>(imagePath);
                PAX_assertNotNull(image, "[TileSetJsonLoader::load] Image file " << imagePath << " could not be loaded!")
            }

            int tilewidth  = j["tilewidth"];
            int tileheight = j["tileheight"];

            std::shared_ptr<TileSet> tileSet = std::make_shared<TileSet>(image, tilewidth, tileheight);
            tileSet->setName(name);
            return tileSet;
        }

        std::shared_ptr<TileSet> TileSetJsonLoader::loadToOrGetFromResources(PAX::Resources &resources,
                                                                             const PAX::VariableHierarchy &parameters) {
            return loadFromPath("TileSetJsonLoader", resources, parameters);
        }
    }
}