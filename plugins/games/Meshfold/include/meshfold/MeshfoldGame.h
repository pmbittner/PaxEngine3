//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PAXTILEDEMO_H
#define PAXENGINE3_PAXTILEDEMO_H

#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/io/event/KeyPressedEvent.h>

#include "polypropylene/log/Log.h"

#include <paxcore/world/property/WorldSize.h>

#include <paxcore/gameentity/GameEntity.h>
#include <paxcore/gameentity/property/behaviours/NoClipControls.h>

#include <paxcore/rendering/graphics/AssetGraphics.h>
#include <paxcore/rendering/graphics/SceneGraphGraphics.h>
#include <paxcore/rendering/geometry/ScreenFillingQuad.h>

#include <paxcore/rendering/factory/ViewportFactory.h>
#include <paxcore/rendering/renderpass/RenderPassFactory.h>
#include <paxcore/rendering/data/Material.h>

#include "Meshfold.h"

namespace PAX {
    class MeshfoldGame : public Game {
        World * uv_world   = nullptr;
        World * mesh_world = nullptr;

        Settings settings;

        std::shared_ptr<Texture> getTexture(const std::shared_ptr<Asset> & asset)
        {
            for (const Asset::Part & p : asset->getMeshes()) {
                if (p.material->diffuse.texture) {
                    return p.material->diffuse.texture;
                }
            }

            for (const std::shared_ptr<Asset> & child : asset->getChildren()) {
                std::shared_ptr<Texture> tex = getTexture(child);
                if (tex) {
                    return tex;
                }
            }

            return nullptr;
        }

        void setTexture(const std::shared_ptr<Asset> & asset, const std::shared_ptr<Texture> & texture)
        {
            for (const Asset::Part & p : asset->getMeshes()) {
                if (p.material->diffuse.texture) {
                    p.material->diffuse.texture = texture;
                }
            }

            for (const std::shared_ptr<Asset> & child : asset->getChildren()) {
                setTexture(child, texture);
            }
        }

    public:
        void initialize() override {
            Game::initialize();

            settings.parse(Services::GetPaths().getResourcePath() + "Meshfold/meshfold.paxconfig");

            const bool showUVWorld = settings.getOrDefault<bool>("showUVWorld");

            auto uvWorldPrefab = Services::GetResources().loadOrGet<WorldPrefab>(settings.get<Path>("UVWorld"));
            uv_world = uvWorldPrefab->create(settings.toVariableRegister());

            auto meshWorldPrefab = Services::GetResources().loadOrGet<WorldPrefab>(settings.get<Path>("MeshWorld"));
            mesh_world = meshWorldPrefab->create(settings.toVariableRegister());

            std::vector<GameEntity *> meshes = mesh_world->getEntitiesWithTag("Meshfold");
            if (meshes.size() == 1) {
                AssetGraphics *g = meshes.at(0)->get<AssetGraphics>();

                if (g) {
                    std::shared_ptr<Texture> meshTexture = getTexture(g->getAsset());
                    if (meshTexture) {
                        uv_world->get<Meshfold>()->setBackground(meshTexture);
                    }

                    if (!showUVWorld) {
                        RenderPassFactory *rpFactory = Services::GetFactoryService().get<RenderPassFactory>();
                        RenderPass *rp = rpFactory->create(uv_world->get<WorldSize>()->getSize2D());
                        rp->addChannel(RenderPassChannel(RenderPassChannel::Colour, Texture::PixelFormat::RGBA));
                        rp->finalize();

                        SceneGraphGenerator *sgg = uv_world->getSceneGraphGenerator();
                        sgg->addRenderPass(rp);
                        setTexture(g->getAsset(), rp->getChannel(RenderPassChannel::Colour).getTexture());
                    }
                }
            }

            addWorld(uv_world);
            addWorld(mesh_world);
        }
    };
}

#endif //PAXENGINE3_PAXTILEDEMO_H
