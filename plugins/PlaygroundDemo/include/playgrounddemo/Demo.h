//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PLAYGROUNDDEMO_H
#define PAXENGINE3_PLAYGROUNDDEMO_H

#include <paxutil/rendering/Cube.h>

#include <paxcore/Game.h>
#include <paxcore/rendering/camera/Camera.h>
#include <paxcore/rendering/camera/PerspectiveProjection.h>
#include <paxcore/rendering/graphics/SceneGraphGraphics.h>
#include <paxcore/rendering/data/Texture.h>
#include <paxcore/entity/property/behaviours/NoClipControls.h>
#include <paxcore/rendering/graphics/AssetGraphics.h>
#include <paxcore/rendering/data/Material.h>
#include <paxcore/rendering/light/DirectionalLight.h>
#include <paxcore/rendering/light/AmbientLight.h>
#include <paxcore/system/entity/LightSystem.h>
#include <paxcore/rendering/factory/ViewportFactory.h>

#include "TestBehaviour.h"

namespace PAX {
    namespace PlaygroundDemo {
        class Demo : public Game {
            World *_world = nullptr;

            std::shared_ptr<Shader> redShader;
            std::shared_ptr<Shader> texShader;
            std::shared_ptr<Shader> simpleMatShader;

            std::shared_ptr<Mesh> cube;

            std::shared_ptr<Material> cubeMaterial;

            void prepareAssets() {
                texShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getResourcePath() + "/shader/test/PlainTexture.vert",
                                Services::GetPaths().getResourcePath() + "/shader/test/PlainTexture.frag"
                        )
                );
                simpleMatShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getResourcePath() + "/shader/material/simple/simplemat.vert",
                                Services::GetPaths().getResourcePath() + "/shader/material/simple/simplemat.frag"
                        )
                );
                redShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getResourcePath() + "/shader/test/red/red.vert",
                                Services::GetPaths().getResourcePath() + "/shader/test/red/red.frag"
                        )
                );

                cube = Util::createCube(true /*with tex coords*/);
                cube->upload();

                std::shared_ptr<Texture> texture = Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().getResourcePath() + "icon/PaxEngine3/PaxEngine3_128.png"
                );
                cubeMaterial = std::make_shared<Material>("CubeMaterial_createdInCode");
                cubeMaterial->diffuse.texture = texture;
            }

            Entity* createCube(std::shared_ptr<Shader> & shader) {
                Entity* cubeEntity = new Entity();
                //*
                std::shared_ptr<Asset> a = std::make_shared<Asset>(std::vector<Asset::Part>{
                        Asset::Part(cube, cubeMaterial)
                });
                AssetGraphics * g = new AssetGraphics(a);
                g->setShader(shader);
                cubeEntity->add(g);
                //*/
                return cubeEntity;
            }

            Entity* createFromFile(const std::string & relativeResourcePath, std::shared_ptr<Shader> & shader) {
                std::shared_ptr<Asset> tree = Services::GetResources().load<Asset>(
                        Services::GetPaths().getResourcePath() + relativeResourcePath
                );
                Entity* treeEntity = new Entity();
                AssetGraphics * g = new AssetGraphics(tree);
                g->setShader(shader);
                treeEntity->add(g);
                return treeEntity;
            }

        public:
            Demo() : Game()
            {

            }

            ~Demo() override = default;

            void onKeyDown(KeyPressedEvent & keyPressedEvent) {
                if (keyPressedEvent.button == PAX::Key::ESCAPE)
                    Engine::Instance().stop();
            }

            void initialize() override {
                Game::initialize();
                this->addSystem(std::make_unique<LightSystem>());

                Services::GetEventService().add<KeyPressedEvent, Demo, &Demo::onKeyDown>(this);

                prepareAssets();

                constexpr bool withCube = true;
                constexpr bool withTree = true;
                constexpr bool withTank = !true;

                _world = new World();
                WorldLayer* mainLayer = new WorldLayer("PlaygroundDemoMainLayer", 3);

                Entity* cam = new Entity();
                {
                    std::shared_ptr<PerspectiveProjection> proj = std::make_shared<PerspectiveProjection>();
                    proj->setFOV(90);
                    cam->add(new Camera(Services::GetFactoryService().get<ViewportFactory>()->create(), proj));
                    cam->add(new NoClipControls());
                    mainLayer->spawn(cam);
                }

                cam->getTransformation().position() = {0, 0, 0};

                if PAX_CONSTEXPR_IF (withCube) {
                    Entity* cube = createCube(simpleMatShader);
                    cube->getTransformation().position() = {0, 0, -4};
                    mainLayer->spawn(cube);
                }

                if PAX_CONSTEXPR_IF (withTree) {
                    Entity* tree  = createFromFile("PlaygroundDemo/mesh/lowpolytree/lowpolytree.obj", simpleMatShader);
                    tree->getTransformation().position() = {-3, 0, -5};
                    mainLayer->spawn(tree);
                }

                if PAX_CONSTEXPR_IF (withTank) {
                    Entity* tank  = createFromFile("PlaygroundDemo/mesh/ltp/LTP.obj", simpleMatShader);
                    tank->getTransformation().position() = {1, -2, -5};
                    mainLayer->spawn(tank);
                }

                // Spawn a light
                Entity* lightEntity = new Entity();
                lightEntity->add(
                        new DirectionalLight(
                                glm::vec3(1, 0, 0),
                                //glm::vec4(1, 0.7f, 0.2, 20)
                                glm::vec4(1, 1, 1, 1)
                        )
                );
                mainLayer->spawn(lightEntity);

                mainLayer->add(new AmbientLight(glm::vec3(0.6, 0, 0.3)));

                _world->addLayer(mainLayer);
                setActiveWorld(_world);
            }
        };
    }
}

#endif //PAXENGINE3_PLAYGROUNDDEMO_H
