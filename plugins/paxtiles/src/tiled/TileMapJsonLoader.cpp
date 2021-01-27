//
// Created by Paul on 31.03.2019.
//

#include <paxtiles/tiled/TileMapJsonLoader.h>
#include <paxcore/service/Services.h>
#include <paxphysics/2d/Hitbox2D.h>
#include <paxphysics/2d/box2d/Box2DHitbox.h>
#include <paxphysics/2d/shape/Rectangle.h>

namespace PAX {
    namespace Tiles {
        bool TileMapJsonLoader::canLoad(PAX::Path path) const {
            return Services::GetResources().getLoader<nlohmann::json>(path) != nullptr;
        }

        std::shared_ptr<TileMap> TileMapJsonLoader::loadOrGetFromJson(PAX::Resources &resources,
                                                                             const nlohmann::json & j) const {
            return resources.loadOrGet<TileMap>(JsonToPath(j));
        }

        std::shared_ptr<TileMap> TileMapJsonLoader::load(PAX::Path path) {
            //std::cout << "[TileMapJsonLoader::load] " << path << std::endl;
            std::shared_ptr<nlohmann::json> jptr = Services::GetResources().loadOrGet<nlohmann::json>(path);
            PAX_ASSERT_NOT_NULL(jptr, "TileMap json file " << path << " could not be loaded!");
            const nlohmann::json & j = *jptr;


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

            // Find z of main layer
            int zOffset = 0;
            bool mainLayerFound = false;
            for (const nlohmann::json & layerj : j["layers"]) {
                const std::string layerName = layerj["name"];
                const std::string layerType = layerj["type"];
//                PAX_LOG(Log::Level::Info, "Inspect layer " << layerType << ": " << layerName);
                if (layerType == "objectgroup" && layerName == "Main") {
//                    PAX_LOG(Log::Level::Info, "Found main layer at z = " << zOffset);
                    mainLayerFound = true;
                    break;
                }
                --zOffset;
            }

            // Parse layers
            int z = 0;
            if (mainLayerFound) {
                z = zOffset;
            }
            for (const nlohmann::json & layerj : j["layers"]) {
                const std::string layerName = layerj["name"];
                const std::string layerType = layerj["type"];

                const bool visible = layerj["visible"];
                if (!visible) {
                    PAX_LOG(Log::Level::Info, "Layer \"" << layerName << "\" is skipped because it is invisible.");
                    continue;
                }

                if (layerType == "tilelayer") {
                    loadTileLayer(layerj, tilemap, tilesets, gids, z);
                } else if (layerType == "objectgroup") {
                    loadObjectGroup(layerj, tilemap, tilesets, gids, z);
                } else if (layerType == "imagelayer") {
                    PAX_LOG(Log::Level::Warn, "Loading imagelayers is not supported yet! Skipping layer \"" << layerName << "\".");
                }
                ++z;
            }

            return tilemap;
        }

        void TileMapJsonLoader::loadTileLayer(
                const nlohmann::json & layerj,
                std::shared_ptr<PAX::Tiles::TileMap> &map,
                const std::vector<std::shared_ptr<TileSet>> & tilesets,
                const std::vector<int> & gids,
                const int z)
        {
            const int layerWidth = layerj["width"];
            const int layerHeight = layerj["height"];

            const int layerX = layerj["x"];
            const int layerY = layerj["y"];
            const float opacity = layerj["opacity"];

            const std::vector<int> tileData = layerj["data"];
            assert(tileData.size() == layerWidth * layerHeight);
            std::vector<Tile> tiles(tileData.size());

            int tileX = layerX;
            int tileY = layerY;
            for (int i = 0; i < tileData.size(); ++i) {
                int datai = tileData[i];
                int tilesetIndex = 0;
                bool isEmpty = false;

                // Detects isEmpty, tilesetIndex and datai somehow
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

                const std::shared_ptr<TileSet> & myTileSet = tilesets[tilesetIndex];
                const int myTileSetWidth = myTileSet->getSpriteSheet().getDimensions().x;

                Tile & tile = tiles[i];
                tile.isEmpty = isEmpty;
                tile.textureColumn = datai % myTileSetWidth;
                tile.textureRow = datai / myTileSetWidth;
                tile.tileSetIndex = tilesetIndex;

                TileInfo & tileInfo = myTileSet->getTileInfo(tile.textureColumn, tile.textureRow);

                // check if tile is solid
                if (tileInfo.isSolid) {
                    const glm::ivec2 & tileSize = myTileSet->getTileSize();
                    GameEntity * tileEntity = pax_new(GameEntity)();
                    tileEntity->i_setMotionType(MotionType::Static);
                    tileEntity->addTag("Tile"); // TODO: Make this a variable

                    // set position
                    tileEntity->getTransformation().position2D() = glm::vec2(
                            tileSize.x * (0.5f + (float)tileX - ((float)layerWidth  / 2.f)),
                            -tileSize.y * (0.5f + (float)tileY - ((float)layerHeight / 2.f))
                            );

                    // add a hitbox because solid
                    // TODO: Indicate to the hitbox if it should be solid or not. CUrrently, everything is solid
                    Physics::Hitbox2D * hitbox = pax_new(Physics::Box2DHitbox)();
                    hitbox->setFixtures({Physics::Fixture2D(
                            std::make_shared<Physics::Rectangle>(tileSize),
                            std::make_shared<Physics::PhysicsMaterial>())});
                    hitbox->setFixedRotation(true);
                    tileEntity->add(hitbox);
                    map->_addGameEntity(tileEntity);
//                    PAX_LOG(Log::Level::Info, "Added hitbox for tile " << tileX << ", " << tileY << " at " << tileEntity->getTransformation().position2D());
                }

                // TODO: Check if has hitbox

                // update pos
                ++tileX;
                if (tileX >= layerX + layerWidth) {
                    tileX = layerX;
                    ++tileY;
                }
            }

            TileMap::Layer & layer = map->addLayer(tiles, layerWidth);
            layer.x = layerX;
            layer.y = layerY;
            layer.z = z;
            layer.opacity = opacity;
            layer.name = layerj["name"];
        }

        void TileMapJsonLoader::loadObjectGroup(const nlohmann::json &layerj,
                                                std::shared_ptr<PAX::Tiles::TileMap> &map,
                                                const std::vector<std::shared_ptr<PAX::Tiles::TileSet>> &tilesets,
                                                const std::vector<int> &gids,
                                                const int z)
        {
            const int layerX = layerj["x"];
            const int layerY = layerj["y"];

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

                Path prefabPath = VariableResolver::resolveVariables(
                        JsonToString(obj["type"]),
                        // We use these predefined variables as these are intended to be used in
                        // all our json resources.
                        // TODO: Move PAX::Prefab::PreDefinedVariables to a more common place like Settings.
                        PAX::IPrefab::PreDefinedVariables);
                if (prefabPath.isEmpty()) {
                    PAX_LOG(Log::Level::Error, "Object with name=" << obj["name"] << ", id=" << obj_id << " has empty type (which should be the path to a prefab).");
                } else {
                    std::shared_ptr<PAX::GameEntityPrefab> prefab = Services::GetResources().loadOrGet<GameEntityPrefab>(
                            prefabPath);

                    if (prefab) {
                        VariableRegister varRegister;
                        if (obj.find("properties") != obj.end()) {
                            for (const nlohmann::json &property : obj["properties"]) {
                                varRegister[property["name"]] =
                                        VariableResolver::resolveVariables(
                                                JsonToString(property["value"]),
                                                PAX::IPrefab::PreDefinedVariables);
                            }
                        }

                        GameEntity *entity = prefab->create(varRegister);
                        Transformation &t = entity->getTransformation();
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
}