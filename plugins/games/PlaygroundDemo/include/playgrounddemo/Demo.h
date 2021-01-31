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
#include <paxcore/gameentity/property/behaviours/NoClipControls.h>
#include <paxcore/rendering/graphics/AssetGraphics.h>
#include <paxcore/rendering/data/Material.h>
#include <paxcore/rendering/light/DirectionalLight.h>
#include <paxcore/rendering/light/AmbientLight.h>
#include <paxcore/system/gameentity/LightSystem.h>
#include <paxcore/rendering/factory/ViewportFactory.h>
#include <paxassimp/AssimpResourceLoader.h>

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
                                Services::GetPaths().getEngineResourceDirectory() + "/shader/test/PlainTexture.vert",
                                Services::GetPaths().getEngineResourceDirectory() + "/shader/test/PlainTexture.frag"
                        )
                );
                simpleMatShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getEngineResourceDirectory() + "/shader/material/simple/simplemat.vert",
                                Services::GetPaths().getEngineResourceDirectory() + "/shader/material/simple/simplemat.frag"
                        )
                );
                redShader = Services::GetResources().loadOrGet<Shader>(
                        Shader::FileInfo(
                                Services::GetPaths().getEngineResourceDirectory() + "/shader/test/red/red.vert",
                                Services::GetPaths().getEngineResourceDirectory() + "/shader/test/red/red.frag"
                        )
                );

                cube = Util::createCube(true /*with tex coords*/);
                cube->upload();

                std::shared_ptr<Texture> texture = Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().getEngineResourceDirectory() + "icon/PaxEngine3/PaxEngine3_128.png"
                );
                cubeMaterial = std::make_shared<Material>("CubeMaterial_createdInCode");
                cubeMaterial->diffuse.texture = texture;
            }

            GameEntity* createCube(std::shared_ptr<Shader> & shader) {
                GameEntity* cubeGameEntity = new GameEntity();
                //*
                std::shared_ptr<Asset> a = std::make_shared<Asset>(std::vector<Asset::Part>{
                        Asset::Part(cube, cubeMaterial)
                });
                AssetGraphics * g = new AssetGraphics(a);
                g->setShader(shader);
                cubeGameEntity->add(g);
                //*/
                return cubeGameEntity;
            }

            GameEntity* createFromFile(const std::string & relativeResourcePath, std::shared_ptr<Shader> & shader) {
                std::shared_ptr<Asset> tree = Services::GetResources().load<Asset>(
                        Services::GetPaths().getEngineResourceDirectory() + relativeResourcePath, AssetImport::Flags::None
                );
                GameEntity* treeGameEntity = new GameEntity();
                AssetGraphics * g = new AssetGraphics(tree);
                g->setShader(shader);
                treeGameEntity->add(g);
                return treeGameEntity;
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
                constexpr bool withTank = true;

                _world = new World("PlaygroundDemo", 3);

                GameEntity* cam = new GameEntity();
                {
                    PerspectiveProjection * proj = new PerspectiveProjection();
                    proj->setFOV(90);
                    cam->add(new Camera(Services::GetFactoryService().get<ViewportFactory>()->create(), proj));
                    cam->add(new NoClipControls());
                    _world->spawn(cam);
                }

                cam->getTransformation().position() = {0, 0, 0};

                PAX_CONSTEXPR_IF (withCube) {
                    GameEntity* cube = createCube(simpleMatShader);
                    cube->getTransformation().position() = {0, 0, -4};
                    _world->spawn(cube);
                }

                PAX_CONSTEXPR_IF (withTree) {
                    GameEntity* tree  = createFromFile("demos/PlaygroundDemo/mesh/lowpolytree/lowpolytree.obj", simpleMatShader);
                    tree->getTransformation().position() = {-3, 0, -5};
                    _world->spawn(tree);
                }

                PAX_CONSTEXPR_IF (withTank) {
                    GameEntity* tank  = createFromFile("demos/PlaygroundDemo/mesh/ltp/LTP.obj", simpleMatShader);
                    tank->getTransformation().position() = {1, -2, -5};
                    _world->spawn(tank);
                }

                // Spawn a light
                GameEntity* lightGameEntity = new GameEntity();
                lightGameEntity->add(
                        new DirectionalLight(
                                glm::vec3(1, 0, 0),
                                //glm::vec4(1, 0.7f, 0.2, 20)
                                glm::vec4(1, 1, 1, 1)
                        )
                );
                _world->spawn(lightGameEntity);

                _world->add(new AmbientLight(glm::vec3(1, 0.5, 0.7)));

                addWorld(_world);
            }
        };
    }
}

#endif //PAXENGINE3_PLAYGROUNDDEMO_H
