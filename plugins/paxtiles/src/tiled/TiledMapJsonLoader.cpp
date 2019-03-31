//
// Created by Paul on 31.03.2019.
//

#include <paxtiles/tiled/TiledMapJsonLoader.h>
#include <paxcore/service/Services.h>
#include <paxutil/json/Json.h>
#include <paxtiles/TileSet.h>

namespace PAX {
    namespace Tiles {
        bool TiledMapJsonLoader::canLoad(PAX::Path path) const {
            return Services::GetResources().getLoader<nlohmann::json>(path) != nullptr;
        }

        std::shared_ptr<TileMap> TiledMapJsonLoader::load(PAX::Path path) {
            std::shared_ptr<nlohmann::json> jptr = Services::GetResources().loadOrGet<nlohmann::json>(path);
            PAX_assertNotNull(jptr, "[TiledMapJsonLoader::load] TileMap json file " << path << " could not be loaded!")
            const nlohmann::json & j = *jptr.get();

            if (j["orientation"] != "orthogonal") {
                std::cerr << "[TiledMapJsonLoader::load] Only orthogonal maps are supported yet! \"orientation\" was " << j["orientation"] << std::endl;
                return nullptr;
            }

            int  width      = j["width"];
            int  height     = j["height"];
            int  tilewidth  = j["tilewidth"];
            int  tileheight = j["tileheight"];
            bool infinite   = j["infinite"];

            std::vector<std::shared_ptr<TileSet>> tilesets;
            std::vector<int> gids;

            for (const nlohmann::json & tilesetj : j["tilesets"]) {
                int firstgid = tilesetj["firstgid"];
                Path tilesetPath = path.getDirectory() + tilesetj["source"];
                std::shared_ptr<TileSet> tileset = Services::GetResources().loadOrGet<TileSet>(tilesetPath);

                // Insert the tileset and firstgid such that the vectors are sorted.
                auto tilesetsIt = tilesets.begin();
                auto gidsIt = gids.begin();

                for (; gidsIt != gids.end(); ++gidsIt, ++tilesetsIt) {
                    auto nextElement = gidsIt + 1;
                    if (nextElement != gids.end() && firstgid < *nextElement) {
                        break;
                    }
                }

                gids.insert(gidsIt, firstgid);
                tilesets.insert(tilesetsIt, tileset);
            }

            std::shared_ptr<TileMap> tilemap = std::make_shared<TileMap>(tilesets, width, height, tilewidth, tileheight);

            // Parse layers
            for (const nlohmann::json & layerj : j["layers"]) {
                if (layerj["type"] == "tilelayer") {
                    int layerWidth = layerj["width"];
                    int layerHeight = layerj["height"];

                    int layerX = layerj["x"];
                    int layerY = layerj["y"];
                    float opacity = layerj["opacity"];
                    int id = layerj["id"];

                    // TODO: Use id to determine z pos and communicate it to let entities have correct z.
                    std::vector<int> tileData = layerj["data"];
                    assert(tileData.size() == layerWidth * layerHeight);
                    std::vector<Tile> tiles(tileData.size());

                    for (int i = 0; i < tileData.size(); ++i) {
                        int datai = tileData[i];
                        int offset = 0;
                        int tilesetIndex = 0;

                        for (int gid : gids) {
                            if (gid < datai) {
                                offset = gid;
                                ++tilesetIndex;
                            } else {
                                break;
                            }
                        }

                        datai -= offset;

                        Tile t{datai % layerWidth, datai / layerHeight, tilesetIndex};
                        tiles.emplace_back(t);
                    }

                    TileMap::Layer layer(tiles, layerWidth);
                    layer.x = layerX;
                    layer.y = layerY;
                    layer.z = id;
                    layer.opacity = opacity;

                    tilemap->addLayer(layer);
                }
            }

            return tilemap;
        }

        std::shared_ptr<TileMap> TiledMapJsonLoader::loadToOrGetFromResources(PAX::Resources &resources,
                                                                              const PAX::VariableHierarchy &parameters) {            return loadFromPath("SDLImageOpenGLTextureLoader", resources, parameters);
            return loadFromPath("TiledMapJsonLoader", resources, parameters);
        }
    }
}