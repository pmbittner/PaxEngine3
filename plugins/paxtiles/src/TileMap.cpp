//
// Created by paul on 03.01.19.
//

#include "paxtiles/TileMap.h"
#include <paxutil/lib/GlmIncludes.h>

#include <vector>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/MeshFactory.h>

namespace PAX {
    namespace Tiles {
        TileMap::Layer::Layer(const std::vector<PAX::Tiles::Tile> & tiles, int width)
        : tiles(tiles), width(width), height(tiles.size() / width)
        {
        }

        void TileMap::Layer::finalize(const std::vector<std::shared_ptr<TileSet>> & tileSets) {
            if (isFinalized()) return;

            std::vector<glm::vec2>  vertices;
            std::vector<glm::ivec3> faces;
            std::vector<float>      tileSheetIds;
            std::vector<glm::vec2>  uv;

            glm::vec3 vertexOffset = -glm::vec3(width, height, 0) / 2.f;
            glm::vec3 flipY = {1, -1, 1};

            // Order of tiles:
            //
            // >>>>>
            // >>>>>
            // >>>>>
            //
            int index = 0;
            for (unsigned long row = 0; row < height; ++row) {
                for (unsigned long column = 0; column < width; ++column) {
                    const Tile & currentTile = tiles[row * width + column];

                    // use vec2 to cast to float
                    const SpriteSheet & spriteSheet = tileSets[currentTile.tileSetIndex]->getSpriteSheet();
                    glm::vec2 spriteSheetSize = spriteSheet.getDimensions();
                    glm::vec2 uvTileSize = 1.f / spriteSheetSize;
                    glm::vec2 uvInsets(0.5f / spriteSheet.getTexture()->getWidth(), 0.5f / spriteSheet.getTexture()->getHeight());
                    //glm::vec2 uvInsets;
                    uvInsets = {0, 0};

                    // We have lots of vertex duplicates here, but this is necessary due to the need
                    // for different UV coords.
                    vertices.emplace_back(flipY * (vertexOffset + glm::vec3(column    , row    , 0)));
                    vertices.emplace_back(flipY * (vertexOffset + glm::vec3(column    , row + 1, 0)));
                    vertices.emplace_back(flipY * (vertexOffset + glm::vec3(column + 1, row + 1, 0)));
                    vertices.emplace_back(flipY * (vertexOffset + glm::vec3(column + 1, row    , 0)));

                    faces.emplace_back(glm::ivec3(index, index + 2, index + 1));
                    faces.emplace_back(glm::ivec3(index, index + 3, index + 2));

                    float uvX = static_cast<float>(currentTile.textureColumn) * uvTileSize.x;
                    float uvY = static_cast<float>(currentTile.textureRow)    * uvTileSize.y;
                    uv.emplace_back(glm::vec2(uvX                + uvInsets.x, uvY                + uvInsets.y));
                    uv.emplace_back(glm::vec2(uvX                + uvInsets.x, uvY + uvTileSize.y - uvInsets.y));
                    uv.emplace_back(glm::vec2(uvX + uvTileSize.x - uvInsets.x, uvY + uvTileSize.y - uvInsets.y));
                    uv.emplace_back(glm::vec2(uvX + uvTileSize.x - uvInsets.x, uvY                + uvInsets.y));


                    if (currentTile.isEmpty) {
                        tileSheetIds.emplace_back(-1);
                        tileSheetIds.emplace_back(-1);
                        tileSheetIds.emplace_back(-1);
                        tileSheetIds.emplace_back(-1);
                    } else {
                        tileSheetIds.emplace_back(currentTile.tileSetIndex);
                        tileSheetIds.emplace_back(currentTile.tileSetIndex);
                        tileSheetIds.emplace_back(currentTile.tileSetIndex);
                        tileSheetIds.emplace_back(currentTile.tileSetIndex);
                    }

                    index += 4;
                }
            }

            MeshFactory* meshFactory = Services::GetFactoryService().get<MeshFactory>();
            PAX_assertNotNull(meshFactory, "MeshFactory can't be null!")
            std::shared_ptr<Mesh> mesh = meshFactory->create(vertices, faces);
            PAX_assertNotNull(mesh, "Mesh can't be null!")
            mesh->addAttribute(Mesh::UVs, uv);
            mesh->addAttribute(Mesh::Unspecified, tileSheetIds);
            mesh->upload();

            meshNode.setMesh(mesh);
            tiles.clear();
        }

        bool TileMap::Layer::isFinalized() const {
            return tiles.empty() && meshNode.getMesh() != nullptr;
        }

        void TileMap::Layer::render(PAX::RenderOptions &renderOptions) {
            //std::cout << "TileMap::Layer::render " << name << std::endl;
            meshNode.render(renderOptions);
        }

        TileMap* TileMap::Layer::getMap() {
            return map;
        }

        TileMap::TileMap(const std::vector<std::shared_ptr<TileSet>> & tileSets,
                         int width,
                         int height,
                         int tilewidth,
                         int tileheight)
                         :
                         tileSets(tileSets),
                         tileSize(tilewidth, tileheight),
                         mapSize(width, height)
        {

        }

        TileMap::Layer & TileMap::addLayer(const std::vector<Tile> & tiles, int width) {
            layers.emplace_back(tiles, width);
            Layer & layer = layers.back();
            layer.map = this;
            layer.finalize(tileSets);
            return layer;
        }

        std::vector<TileMap::Layer>& TileMap::getLayers() {
            return layers;
        }

        const std::vector<std::shared_ptr<TileSet>>& TileMap::getTileSets() {
            return tileSets;
        }

        const glm::ivec2 & TileMap::getTileSize() const {
            return tileSize;
        }
    }
}