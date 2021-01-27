//
// Created by Paul on 31.03.2019.
//

#include <paxtiles/tiled/TileSetJsonLoader.h>
#include <paxcore/service/Services.h>
#include <polypropylene/log/Assert.h>

namespace PAX {
    namespace Tiles {
        bool TileSetJsonLoader::canLoad(PAX::Path path) const {
            return Services::GetResources().getLoader<nlohmann::json>(path) != nullptr;
        }

        std::shared_ptr<TileSet> TileSetJsonLoader::load(PAX::Path path) {
            //std::cout << "[TileSetJsonLoader::load] " << path << std::endl;
            std::shared_ptr<nlohmann::json> jptr = Services::GetResources().loadOrGet<nlohmann::json>(path);
            PAX_ASSERT_NOT_NULL(jptr, "[TileSetJsonLoader::load] TileSet json file " << path << " could not be loaded!");
            const nlohmann::json & j = *jptr;

            // load name
            const std::string & name = j["name"];

            // load image
            std::shared_ptr<Texture> image;
            {
                Path imagePath = path.getDirectory() + j["image"];
                image = Services::GetResources().loadOrGet<Texture>(imagePath);
                image->setWrapMode(Texture::WrapMode::ClampToEdge, Texture::WrapMode::ClampToEdge);
                PAX_ASSERT_NOT_NULL(image, "Image file " << imagePath << " could not be loaded!");
            }

            // determine dimensions
            const int columns = j["imagewidth" ].get<int>() / j["tilewidth"].get<int>();
            const int rows    = j["imageheight"].get<int>() / j["tileheight"].get<int>();

            // load tile metadata
            const int numTiles = j["tilecount"].get<int>();
            PAX_ASSERT(columns * rows == numTiles);
            TileInfo * tileInfo = new TileInfo[numTiles];
            if (j.count("tiles") > 0) {
                for (const nlohmann::json &jTileInfo : j["tiles"]) {
                    const int tileId = jTileInfo["id"];
                    // parse tile properties
                    if (jTileInfo.count("properties") > 0) {
                        for (const nlohmann::json &jTileProp : jTileInfo["properties"]) {
//                            PAX_LOG(Log::Level::Info, "Found tile props for " << tileId << ": " << jTileProp);

                            // TODO: Make this extensible to add own properties
                            if (jTileProp["name"] == "solid") {
//                                PAX_LOG(Log::Level::Info, "Found solid tile");
                                tileInfo[tileId].isSolid = jTileProp["value"];
                            }
                        }
                    }
                    // parse tile objectgroup (e.g., hitboxes)
                    if (jTileInfo.count("objectgroup") > 0) {
                        // PAX_NOT_IMPLEMENTED();
                    }
                }
            }

            std::shared_ptr<TileSet> tileSet = std::make_shared<TileSet>(image, columns, rows, tileInfo);
            tileSet->setName(name);
            return tileSet;
        }

        std::shared_ptr<TileSet> TileSetJsonLoader::loadOrGetFromJson(PAX::Resources &resources,
                                                                             const nlohmann::json & j) const {
            return resources.loadOrGet<TileSet>(JsonToPath(j));
        }
    }
}