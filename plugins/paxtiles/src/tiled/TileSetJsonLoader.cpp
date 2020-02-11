//
// Created by Paul on 31.03.2019.
//

#include <paxtiles/tiled/TileSetJsonLoader.h>
#include <paxcore/service/Services.h>
#include <polypropylene/serialisation/json/Json.h>
#include <paxcore/rendering/data/Texture.h>

namespace PAX {
    namespace Tiles {
        bool TileSetJsonLoader::canLoad(PAX::Path path) const {
            return Services::GetResources().getLoader<nlohmann::json>(path) != nullptr;
        }

        std::shared_ptr<TileSet> TileSetJsonLoader::load(PAX::Path path) {
            //std::cout << "[TileSetJsonLoader::load] " << path << std::endl;
            std::shared_ptr<nlohmann::json> jptr = Services::GetResources().loadOrGet<nlohmann::json>(path);
            PAX_ASSERT_NOT_NULL(jptr, "[TileSetJsonLoader::load] TileSet json file " << path << " could not be loaded!");
            const nlohmann::json & j = *jptr.get();

            const std::string & name = j["name"];
            std::shared_ptr<Texture> image;
            {
                Path imagePath = path.getDirectory() + j["image"];
                image = Services::GetResources().loadOrGet<Texture>(imagePath);
                image->setWrapMode(Texture::WrapMode::ClampToEdge, Texture::WrapMode::ClampToEdge);
                PAX_ASSERT_NOT_NULL(image, "[TileSetJsonLoader::load] Image file " << imagePath << " could not be loaded!");
            }

            int columns = j["imagewidth" ].get<int>() / j["tilewidth"].get<int>();
            int rows    = j["imageheight"].get<int>() / j["tileheight"].get<int>();

            std::shared_ptr<TileSet> tileSet = std::make_shared<TileSet>(image, columns, rows);
            tileSet->setName(name);
            return tileSet;
        }

        std::shared_ptr<TileSet> TileSetJsonLoader::loadOrGetFromJson(PAX::Resources &resources,
                                                                             const nlohmann::json & j) const {
            return resources.loadOrGet<TileSet>(JsonToPath(j));
        }
    }
}