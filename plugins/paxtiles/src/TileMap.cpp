//
// Created by paul on 03.01.19.
//

#include <paxtiles/TileMap.h>
#include <paxutil/lib/GlmIncludes.h>

#include <vector>
#include <paxcore/service/Services.h>

namespace PAX {
    namespace Tiles {
        TileMap::TileMap() = default;

        void TileMap::createMesh(const std::vector<std::vector<Tile>> & tiles) {
            // TODO: Make vertices 2d
            std::vector<glm::vec3>  vertices;
            std::vector<glm::ivec3> faces;
            std::vector<glm::vec2>  uv;

            glm::vec3 vertexOffset = -glm::vec3(columns, rows, 0) / 2.f;

            // use vec2 to cast to float
            glm::vec2 spriteSheetSize = spriteSheet->getDimensions();
            glm::vec2 uvTileSize = 1.f / spriteSheetSize;

            // Order of tiles:
            //
            // >>>>>
            // >>>>>
            // >>>>>
            //
            int index = 0;
            for (unsigned long row = 0; row < rows; ++row) {
                for (unsigned long column = 0; column < columns; ++column) {
                    const Tile & currentTile = tiles[row][column];

                    vertices.emplace_back(vertexOffset + glm::vec3(column    , row    , 0));
                    vertices.emplace_back(vertexOffset + glm::vec3(column    , row + 1, 0));
                    vertices.emplace_back(vertexOffset + glm::vec3(column + 1, row + 1, 0));
                    vertices.emplace_back(vertexOffset + glm::vec3(column + 1, row    , 0));

                    faces.emplace_back(glm::ivec3(index, index + 2, index + 1));
                    faces.emplace_back(glm::ivec3(index, index + 3, index + 2));

                    float uvX = static_cast<float>(currentTile.textureColumn) * uvTileSize.x;
                    float uvY = static_cast<float>(currentTile.textureRow)    * uvTileSize.y;
                    uv.emplace_back(glm::vec2(uvX               , uvY));
                    uv.emplace_back(glm::vec2(uvX               , uvY + uvTileSize.y));
                    uv.emplace_back(glm::vec2(uvX + uvTileSize.x, uvY + uvTileSize.y));
                    uv.emplace_back(glm::vec2(uvX + uvTileSize.x, uvY));

                    index += 4;
                }
            }

            mesh = Services::GetFactory().create<Mesh>(&vertices, &faces);
            PAX_assertNotNull(mesh, "Mesh can't be null!");
            mesh->addAttribute(Mesh::UVs, uv);
            mesh->upload();
        }

        void TileMap::create(const std::vector<std::vector<Tile>> & tiles, const std::shared_ptr<SpriteSheet> & spriteSheet) {
            this->columns = tiles.size();
            this->rows    = tiles.at(0).size();
            this->spriteSheet = spriteSheet;
            createMesh(tiles);
        }

        const std::shared_ptr<SpriteSheet> TileMap::getSpriteSheet() const {
            return spriteSheet;
        }

        const std::shared_ptr<Mesh>& TileMap::getMesh() const {
            return mesh;
        }

        unsigned long TileMap::getColumns() const {
            return columns;
        }

        unsigned long TileMap::getRows() const {
            return rows;
        }
    }
}