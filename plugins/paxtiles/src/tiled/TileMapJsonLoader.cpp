//
// Created by Paul on 31.03.2019.
//

#include <paxtiles/tiled/TileMapJsonLoader.h>
#include <paxcore/service/Services.h>

#include <polypropylene/serialisation/json/JsonUtil.h>
#include <polypropylene/serialisation/json/Json.h>

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
            PAX_ASSERT_NOT_NULL(jptr, "[TileMapJsonLoader::load] TileMap json file " << path << " could not be loaded!");
            const nlohmann::json & j = *jptr.get();


            if (j["orientation"] != "orthogonal") {
                PAX_LOG(Log::Level::Error, "Only orthogonal maps are supported yet! \"orientation\" was " << j["orientation"]);
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
            const int layerX = layerj["x"];
            const int layerY = layerj["y"];
            const int z = layerj["id"];

            const glm::vec2 mapSize = map->getSizeInTiles() * map->getTileSize();

            for (const nlohmann::json & obj : layerj["objects"]) {
                const GameEntityID obj_id = obj["id"];
                const glm::ivec2 obj_size(obj["width"], obj["height"]);
                glm::vec2 obj_pos = {0, 0};
                obj_pos += glm::vec2(obj_size) / 2.0f;
                obj_pos += -mapSize / 2.0f;
                obj_pos += glm::vec2(obj["x"].get<int>(), obj["y"].get<int>());
                obj_pos += glm::vec2(layerX, layerY);
                obj_pos.y *= -1;

                VariableRegister varRegister;
                Path prefabPath = VariableResolver::resolveVariables(
                        JsonToString(obj["type"]),
                        // We use these predefined variables as these are intended to be used in
                        // all our json resources.
                        // TODO: Move PAX::Prefab::PreDefinedVariables to a more common place like Settings.
                        PAX::IPrefab::PreDefinedVariables);
                std::shared_ptr<PAX::GameEntityPrefab> prefab = Services::GetResources().loadOrGet<GameEntityPrefab>(prefabPath);

                if (obj.find("properties") != obj.end()) {
                    for (const nlohmann::json &property : obj["properties"]) {
                        varRegister[property["name"]] =
                                VariableResolver::resolveVariables(
                                        JsonToString(property["value"]),
                                        PAX::IPrefab::PreDefinedVariables);
                    }
                }

                if (prefab) {
                    GameEntity * entity = prefab->create(varRegister);
                    Transformation & t = entity->getTransformation();
                    t.position() = {obj_pos.x, obj_pos.y, z};
                    // TODO: This is some sort of hack for our orange boxes for now, where we know, that these have
                    //       size 1px x 1px. Find a better solution for this like primitives as entities or so like:
                    //       Rectangle { Size, RectangleGraphics? }
                    t.setScale(t.getScale() * glm::vec3(obj_size, 1));
                    map->_addGameEntity(entity, obj_id);
                } else {
                    PAX_LOG(Log::Level::Warn, "Object without prefab given. Thus, it will be skipped.");
                }
            }
        }
    }
}