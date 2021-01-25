//
// Created by paul on 03.01.19.
//

#include <paxcore/world/property/WorldSize.h>
#include <paxutil/reflection/EngineFieldFlags.h>
#include "paxtiles/TileMapProperty.h"
#include "paxtiles/TileMapGraphics.h"

namespace PAX {
    namespace Tiles {
        PAX_PROPERTY_IMPL(PAX::Tiles::TileMapProperty)

        void TileMapProperty::init() {
            if (tileMapShader == nullptr) {
                static constexpr const int NUM_MAX_TILESETS = 16;

                Shader::Flags flags;
                flags.VertexFlags   += "\n#define NUM_MAX_TILESETS " + std::to_string(NUM_MAX_TILESETS);
                flags.FragmentFlags += "\n#define NUM_MAX_TILESETS " + std::to_string(NUM_MAX_TILESETS);

                tileMapShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getEngineResourceDirectory() + "/shader/tilemap/tilemap.vert",
                                Services::GetPaths().getEngineResourceDirectory() + "/shader/tilemap/tilemap.frag"
                        ),
                        flags
                );


                tileMapShader->bind();

                for (int i = 0; i < NUM_MAX_TILESETS; ++i) {
                    std::stringstream stream;
                    stream << "tileSets[" << i << "]";
                    if (!tileMapShader->setUniform(stream.str(), i)) {
                        PAX_LOG(Log::Level::Error, "Could not set uniform " << stream.str());
                    }
                }

                tileMapShader->unbind();
            }

            layerEntities = std::vector<GameEntity>(tileMap->getLayers().size());

            int i = 0;
            for (TileMap::Layer & layer : tileMap->getLayers()) {
                auto graphics = pax_new(TileMapGraphics)(layer);
                graphics->setShader(tileMapShader);
                GameEntity & e = layerEntities[i];
                e.add(graphics);
                e.getTransformation().z() = static_cast<float>(layer.z);
                ++i;
            }
        }

        void TileMapProperty::created() {
            Super::created();
            init();
        }

        ClassMetadata TileMapProperty::getMetadata() {
            ClassMetadata m = Super::getMetadata();
            m.add(paxfieldalias("map", tileMap)).flags |= Field::IsMandatory | EngineFieldFlags::IsResource;
            m.add(paxfieldof(scale));
            return m;
        }

        std::shared_ptr<Shader> TileMapProperty::tileMapShader = nullptr;

        TileMapProperty::TileMapProperty(const std::shared_ptr<TileMap> & tilemap) :
            tileMap(tilemap),
            scale(1)
        {
            init();
        }

        TileMapProperty::TileMapProperty() = default;

        void TileMapProperty::attached(PAX::World & world) {
            const glm::ivec2 worldSize = tileMap->getTileSize() * tileMap->getSizeInTiles();

            WorldSize * worldLayerSize = getOwner()->get<WorldSize>();
            if (!worldLayerSize) {
                worldLayerSize = pax_new(WorldSize)(glm::vec3(worldSize, -1));
                getOwner()->add(worldLayerSize);
            } else {
                worldLayerSize->setSize2D(worldSize);
            }

            for (GameEntity & e : layerEntities) {
                world.spawn(&e);
            }

            //*
            for (const std::pair<GameEntity *, GameEntityID> & ep : tileMap->getEntities()) {
                world.getGameEntityIDService().reserveIDFor(ep.first, ep.second);
                world.spawn(ep.first);
            }
            //*/
        }

        void TileMapProperty::detached(PAX::World & world) {
            for (GameEntity & e : layerEntities) {
                if (e.getWorld() == &world) {
                    world.despawn(&e);
                }
            }

            //*
            for (const std::pair<GameEntity *, GameEntityID> & ep : tileMap->getEntities()) {
                GameEntity * e = ep.first;
                if (e->getWorld() == &world) {
                    world.despawn(e);
                }
            }
            //*/
        }

        void TileMapProperty::setScale(const glm::vec3 & scale) {
            glm::vec3 delta = scale / getScale();

            for (GameEntity & e : layerEntities) {
                Transformation & t = e.getTransformation();
                t.setScale(t.getScale() * delta);
            }

            this->scale = scale;
        }

        const glm::vec3& TileMapProperty::getScale() const {
            return scale;
        }
    }
}