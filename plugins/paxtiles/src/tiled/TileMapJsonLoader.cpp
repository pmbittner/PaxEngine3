//
// Created by Paul on 31.03.2019.
//

#include <paxtiles/tiled/TileMapJsonLoader.h>
#include <paxcore/service/Services.h>
#include <paxtiles/TileSet.h>
#include <paxutil/json/JsonUtil.h>

namespace PAX {
    namespace Tiles {
        bool TileMapJsonLoader::canLoad(PAX::Path path) const {
            return Services::GetResources().getLoader<nlohmann::json>(path) != nullptr;
        }

        std::shared_ptr<TileMap> TileMapJsonLoader::loadToOrGetFromResources(PAX::Resources &resources,
                                                                             const PAX::VariableHierarchy &parameters) {
            return loadFromPath("TileMapJsonLoader", resources, parameters);
        }

        std::shared_ptr<TileMap> TileMapJsonLoader::load(PAX::Path path) {
            //std::cout << "[TileMapJsonLoader::load] " << path << std::endl;
            std::shared_ptr<nlohmann::json> jptr = Services::GetResources().loadOrGet<nlohmann::json>(path);
            PAX_assertNotNull(jptr, "[TileMapJsonLoader::load] TileMap json file " << path << " could not be loaded!")
            const nlohmann::json & j = *jptr.get();


            if (j["orientation"] != "orthogonal") {
                std::cerr << "[TileMapJsonLoader::load] Only orthogonal maps are supported yet! \"orientation\" was " << j["orientation"] << std::endl;
                return nullptr;
            }

            int  width      = j["width"];
            int  height     = j["height"];
            int  tilewidth  = j["tilewidth"];
            int  tileheight = j["tileheight"];
            //bool infinite   = j["infinite"];

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

            /*
            for (int i = 0; i < gids.size(); ++i) {
                std::cout << gids[i] << " -> " << tilesets[i]->getName() << std::endl;
            }
            //*/

            std::shared_ptr<TileMap> tilemap = std::make_shared<TileMap>(tilesets, width, height, tilewidth, tileheight);

            // Parse layers
            for (const nlohmann::json & layerj : j["layers"]) {
                std::string layerType = layerj["type"];

                if (layerType == "tilelayer") {
                    loadTileLayer(layerj, tilemap, tilesets, gids);
                } else if (layerType == "objectgroup") {
                    loadObjectGroup(layerj, tilemap, tilesets, gids);
                }
            }

            return tilemap;
        }

        void TileMapJsonLoader::loadTileLayer(
                const nlohmann::json & layerj,
                std::shared_ptr<PAX::Tiles::TileMap> &map,
                const std::vector<std::shared_ptr<TileSet>> & tilesets,
                const std::vector<int> & gids)
        {
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
                int tilesetIndex = 0;
                bool isEmpty = false;

                for (int k = 0; k < gids.size(); ++k) {
                    int cur_gid  = gids[k];
                    int next_gid = std::numeric_limits<int>::max();

                    if (k + 1 < gids.size())
                        next_gid = gids[k + 1];

                    if (cur_gid <= datai && datai < next_gid) {
                        datai -= cur_gid;
                        tilesetIndex = k;
                        break;
                    } else if (datai < cur_gid) {
                        // This should only happen, if the id is less than the very first gid.
                        // This encodes transparency.
                        isEmpty = true;
                        break;
                    }
                }

                int myTileSetWidth = tilesets[tilesetIndex]->getSpriteSheet().getDimensions().x;

                tiles[i].isEmpty = isEmpty;
                tiles[i].textureColumn = datai % myTileSetWidth;
                tiles[i].textureRow = datai / myTileSetWidth;
                tiles[i].tileSetIndex = tilesetIndex;
            }

            TileMap::Layer & layer = map->addLayer(tiles, layerWidth);
            layer.x = layerX;
            layer.y = layerY;
            layer.z = id;
            layer.opacity = opacity;
            layer.name = layerj["name"];
        }

        void TileMapJsonLoader::loadObjectGroup(const nlohmann::json &layerj, std::shared_ptr<PAX::Tiles::TileMap> &map,
                                                const std::vector<std::shared_ptr<PAX::Tiles::TileSet>> &tilesets,
                                                const std::vector<int> &gids)
        {
            int x = layerj["x"];
            int y = layerj["y"];
            int z = layerj["id"];

            for (const nlohmann::json & obj : layerj["objects"]) {

                int obj_x = obj["x"];
                int obj_y = obj["y"];
                int obj_id = obj["id"];
                int obj_width = obj["width"];
                int obj_height = obj["height"];
                PAX_PRINT_OUT("Loading object with id " << obj_id)

                obj_x += x;
                obj_y += y;

                VariableRegister varRegister;
                std::shared_ptr<PAX::EntityPrefab> prefab;

                varRegister["position"] =
                        "[" + std::to_string(obj_x) + ", "
                        + std::to_string(obj_y) + ", "
                        + std::to_string(z) + "]";
                varRegister["scale"] =
                        "[" + std::to_string(obj_width) + ", "
                        + std::to_string(obj_height) + ", 1]";

                for (const nlohmann::json & property : obj["properties"]) {
                    PAX_PRINT_OUT("\tLoading property " << property)
                    std::string property_name = property["name"];
                    std::string property_value =
                            VariableResolver::resolveVariables(
                                    JsonToString(property["value"]),
                                    // We use these predefined variables as these are intended to be used in
                                    // all our json resources.
                                    // TODO: Move PAX::Prefab::PreDefinedVariables to a more common place.
                                    PAX::Prefab::PreDefinedVariables);

                    PAX_PRINT_OUT("\t => " << property_name << " = " << property_value)
                    if (property_name == "prefab") {
                        prefab = Services::GetResources().loadOrGet<EntityPrefab>(Path(property_value));
                    } else {
                        varRegister[property_name] = property_value;
                    }
                }

                if (prefab) {
                    PAX_PRINT_OUT("create Entity")
                    Entity * entity = prefab->create(varRegister);
                    PAX_PRINT_OUT("Entity created")
                    map->_addEntity(entity);
                    PAX_PRINT_OUT("Entity added")
                } else {
                    PAX_PRINT_WARN("Object without prefab given. Thus, it will be skipped.")
                }
            }
        }
    }
}