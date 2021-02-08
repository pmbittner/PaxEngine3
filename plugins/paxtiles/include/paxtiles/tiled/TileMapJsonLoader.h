//
// Created by Paul on 31.03.2019.
//

#ifndef PAXENGINE3_TILEMAPJSONLOADER_H
#define PAXENGINE3_TILEMAPJSONLOADER_H

#include <paxutil/resources/ResourceLoader.h>
#include <polypropylene/serialisation/json/nlohmann/JsonFwd.h>
#include "../TileMap.h"

namespace PAX {
    namespace Tiles {
        /**
         * Loads a TileMap from a path pointing to a json file.
         * The json file has to be created with the Tiled Map Editor (mapeditor.org).
         * Tiled supports custom values.
         * We currently use:
         * for TileMaps:
         * - An objectgroup layer with the name "Main" will be considered as the central layer.
         *   It will get z=0 and all other layers are shifted accordingly.
         *   That way, you can safely place your entities at any z value between -1 and 1.
         * - The "type" of objects in an objectgroup layer is interpreted as a path to a prefab file from
         *   which that object can be constructed.
         * for TileSets:
         * - Any tile with the custom boolean property "solid" set to true, will be considered solid by
         *   the physics system. It will get a quadratic hitbox fitting that tile.
         */
        class TileMapJsonLoader : public ResourceLoader<TileMap, Path> {
#define PAX_TILED_NAME static constexpr const char*
            PAX_TILED_NAME MainLayerName = "Main";
            struct TiledName {
                PAX_TILED_NAME Orientation = "orientation";
                PAX_TILED_NAME Objects = "objects";
                PAX_TILED_NAME Layers = "layers";
                PAX_TILED_NAME TileSets = "tilesets";
                PAX_TILED_NAME TileLayer = "tilelayer";
                PAX_TILED_NAME ObjectLayer = "objectgroup";
                PAX_TILED_NAME ImageLayer = "imagelayer";
                PAX_TILED_NAME Width = "width";
                PAX_TILED_NAME Height = "height";
                PAX_TILED_NAME TileWidth = "tilewidth";
                PAX_TILED_NAME TileHeight = "tileheight";
                struct Orientations {
                    PAX_TILED_NAME Orthogonal = "orthogonal";
                };
                struct Layer {
                    PAX_TILED_NAME Name = "name";
                    PAX_TILED_NAME Type = "type";
                    PAX_TILED_NAME X = "x";
                    PAX_TILED_NAME Y = "y";
                    PAX_TILED_NAME Width = "width";
                    PAX_TILED_NAME Height = "height";
                    PAX_TILED_NAME Opacity = "opacity";
                    PAX_TILED_NAME Data = "data";
                    PAX_TILED_NAME Visible = "visible";
                };
                struct TileSet {
                    PAX_TILED_NAME FirstGID = "firstgid";
                    PAX_TILED_NAME Source = "source";
                };
                struct Object {
                    PAX_TILED_NAME Id = "id";
                    PAX_TILED_NAME Name = "name";
                    PAX_TILED_NAME Type = "type";
                    PAX_TILED_NAME Width = "width";
                    PAX_TILED_NAME Height = "height";
                    PAX_TILED_NAME X = "x";
                    PAX_TILED_NAME Y = "y";
                    PAX_TILED_NAME Properties = "properties";
                    PAX_TILED_NAME Rotation = "rotation";
                    PAX_TILED_NAME CustomPropertiesName = "name";
                    PAX_TILED_NAME CustomPropertiesValue = "value";
                };
            };
#undef PAX_TILED_NAME

            void loadTileLayer(
                    const nlohmann::json & layerj,
                    std::shared_ptr<TileMap> & map,
                    const std::vector<std::shared_ptr<TileSet>> & tilesets,
                    const std::vector<int> & gids,
                    const int z);

            void loadObjectGroup(
                    const nlohmann::json & layerj,
                    std::shared_ptr<TileMap> & map,
                    const std::vector<std::shared_ptr<TileSet>> & tilesets,
                    const std::vector<int> & gids,
                    const int z);

        public:
            PAX_NODISCARD bool canLoad(Path) const override;
            PAX_NODISCARD std::shared_ptr<TileMap> load(Path) override;
            PAX_NODISCARD std::shared_ptr<TileMap> loadOrGetFromJson(Resources &resources, const nlohmann::json & j) const override;
        };
    }
}

#endif //PAXENGINE3_TILEMAPJSONLOADER_H
