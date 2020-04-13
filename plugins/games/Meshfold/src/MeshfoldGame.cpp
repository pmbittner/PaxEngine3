//
// Created by Paul Bittner on 13.04.2020.
//

#include <meshfold/MeshfoldGame.h>
#include <meshfold/util/AssetUtils.h>
#include <paxcore/rendering/data/Material.h>

namespace PAX {
    void MeshfoldGame::initialize() {
        Game::initialize();
        Services::GetEventService().add<KeyPressedEvent, MeshfoldGame, &MeshfoldGame::onKeyDown>(this);
        settings.parse(Services::GetPaths().getResourcePath() + "Meshfold/meshfold.paxconfig");
        settings.set("resolutionWidth_half", std::to_string(
                settings.getOrDefault<int>("resolutionWidth") / 2
                ));

        const std::shared_ptr<Window> & window = Services::GetWindowService().getWindow();
        window->setResolution({
            settings.get<int>("resolutionWidth"),
            settings.get<int>("resolutionHeight")
        });
        window->setFullscreen(settings.getOrDefault<bool>("fullscreen"));

        auto uvWorldPrefab = Services::GetResources().loadOrGet<WorldPrefab>(settings.get<Path>("UVWorld"));
        uv_world = uvWorldPrefab->create(settings.toVariableRegister());

        auto meshWorldPrefab = Services::GetResources().loadOrGet<WorldPrefab>(settings.get<Path>("MeshWorld"));
        mesh_world = meshWorldPrefab->create(settings.toVariableRegister());

        std::vector<GameEntity *> meshes = mesh_world->getEntitiesWithTag("Meshfold");
        if (meshes.size() == 1) {
            AssetGraphics *g = meshes.at(0)->get<AssetGraphics>();

            if (g) {
                std::shared_ptr<Texture> meshTexture = AssetUtils::getFirstTextureYouCanFind(g->getAsset());
                if (meshTexture) {
                    uv_world->get<Meshfold>()->setBackground(meshTexture);
                }

                RenderPassFactory *rpFactory = Services::GetFactoryService().get<RenderPassFactory>();
                uvRenderPass = rpFactory->create(uv_world->get<WorldSize>()->getSize2D());
                uvRenderPass->addChannel(RenderPassChannel(RenderPassChannel::Colour, Texture::PixelFormat::RGBA));
                uvRenderPass->finalize();

                SceneGraphGenerator *sgg = uv_world->getSceneGraphGenerator();
                sgg->addRenderPass(uvRenderPass);
                AssetUtils::setAllDiffuseTextures(
                        g->getAsset(),
                        uvRenderPass->getChannel(RenderPassChannel::Colour).getTexture());
            }
        }

        addWorld(uv_world);
        addWorld(mesh_world);
    }

    void MeshfoldGame::terminate() {
        Services::GetEventService().remove<KeyPressedEvent, MeshfoldGame, &MeshfoldGame::onKeyDown>(this);
        Game::terminate();
    }

    void MeshfoldGame::toggleShowUVWorld() {
        if (!screen_world) {
            const Path shaderPath = Services::GetPaths().getResourcePath() + "/Meshfold/shader/screen";

            auto screenWorldPrefab = Services::GetResources().loadOrGet<WorldPrefab>(settings.get<Path>("ScreenWorld"));
            screen_world = screenWorldPrefab->create(settings.toVariableRegister());

            std::shared_ptr<Material> mat = std::make_shared<Material>("ScreenMat");
            mat->diffuse.texture = uvRenderPass->getChannel(RenderPassChannel::Colour).getTexture();
            std::shared_ptr<Mesh> screenQuad = CreateScreenFillingQuad();
            screenQuad->upload();
            std::shared_ptr<Asset> a = std::make_shared<Asset>(
                    std::vector<Asset::Part>{Asset::Part(screenQuad, mat)});

            AssetGraphics * g = new (GameEntity::GetPropertyAllocator().allocate<AssetGraphics>()) AssetGraphics(a);
            g->setShader(Services::GetResources().loadOrGet<Shader>(Shader::FileInfo(
                    shaderPath + "/screen.vert",
                    shaderPath + "/screen.frag")));

            GameEntity * screen = new GameEntity();
            screen->add(g);
            screen_world->spawn(screen);
        }

        Camera * meshCam = nullptr;
        {
            const auto & meshCams = mesh_world->getEntitiesWithTag(Tags::Camera);
            if (meshCams.size() == 1) {
                meshCam = meshCams.at(0)->get<Camera>();
            } else {
                PAX_THROW_RUNTIME_ERROR("");
            }
        }
        Viewport & v = meshCam->getViewport();
        const std::shared_ptr<Window>& window = Services::GetWindowService().getWindow();
        glm::ivec2 win_res = window->getResolution();

        if (hasWorld(screen_world)) {
            v.setWidth(win_res.x);
            removeWorld(screen_world);
        } else {
            v.setWidth(win_res.x / 2);
            addWorld(screen_world);
        }
    }

    void MeshfoldGame::onKeyDown(KeyPressedEvent & e) {
        if (!e.repeated) {
            if (e.button == Key::F1) {
                toggleShowUVWorld();
            } else if (e.button == Key::ESCAPE) {
                Engine::Instance().stop();
            }
        }
    }
}