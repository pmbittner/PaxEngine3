//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PLAYGROUNDDEMO_H
#define PAXENGINE3_PLAYGROUNDDEMO_H

#include <core/Game.h>

#include <core/rendering/camera/Camera.h>
#include <core/rendering/camera/PerspectiveProjection.h>
#include <utility/rendering/Cube.h>
#include <core/rendering/graphics/SceneGraphGraphics.h>
#include <core/rendering/graphics/nodes/MeshNode.h>
#include <core/rendering/graphics/nodes/TexturingNode.h>
#include <core/rendering/data/Texture.h>
#include <core/entity/component/behaviours/NoClipControls.h>
#include <core/rendering/graphics/AssetGraphics.h>
#include <core/rendering/data/Material.h>

#include "TestBehaviour.h"

namespace PAX {
    namespace PlaygroundDemo {
        class Demo : public Game {
            World *_world;
            std::shared_ptr<Shader> redShader;
            std::shared_ptr<Shader> texShader;
            std::shared_ptr<Shader> simpleMatShader;
            std::shared_ptr<Mesh> cube;
            std::shared_ptr<Material> cubeMaterial;

            void prepareAssets() {
                texShader = Services::GetResources().loadOrGet<Shader>(
                        Services::GetPaths().getAbsoluteResourcePath() + "shader/test/PlainTexture.vert",
                        Services::GetPaths().getAbsoluteResourcePath() + "shader/test/PlainTexture.frag"
                );
                texShader->upload();
                simpleMatShader = Services::GetResources().loadOrGet<Shader>(
                        Services::GetPaths().getAbsoluteResourcePath() + "shader/material/simple/simplemat.vert",
                        Services::GetPaths().getAbsoluteResourcePath() + "shader/material/simple/simplemat.frag"
                );
                simpleMatShader->upload();
                redShader = Services::GetResources().loadOrGet<Shader>(
                        Services::GetPaths().getAbsoluteResourcePath() + "shader/test/red/red.vert",
                        Services::GetPaths().getAbsoluteResourcePath() + "shader/test/red/red.frag"
                );
                redShader->upload();

                cube = Util::createCube(true /*with tex coords*/);
                cube->upload();

                std::shared_ptr<Texture> texture = Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().getAbsoluteResourcePath() + "img/PaxEngine3_128.png"
                );
                cubeMaterial = std::make_shared<Material>("CubeMaterial_createdInCode");
                cubeMaterial->diffuse.texture = texture;
            }

            Entity* createCube(std::shared_ptr<Shader> & shader) {
                Entity* cubeEntity = new Entity();
                EntityComponentService& es = Services::GetEntityComponentService();
                std::shared_ptr<Asset> a = std::make_shared<Asset>(std::vector<Asset::Part>{
                        Asset::Part(cube, cubeMaterial)
                });
                AssetGraphics* g = es.create<AssetGraphics>(a);
                g->setShader(shader);
                cubeEntity->add(g);
                return cubeEntity;
            }

            Entity* createFromFile(const std::string & relativeResourcePath, std::shared_ptr<Shader> & shader) {
                EntityComponentService& es = Services::GetEntityComponentService();
                std::shared_ptr<Asset> tree = Services::GetResources().load<Asset>(
                        Services::GetPaths().getAbsoluteResourcePath() + relativeResourcePath
                );
                Entity* treeEntity = new Entity();
                AssetGraphics* g = es.create<AssetGraphics>(tree);
                g->setShader(shader);
                treeEntity->add(g);
                return treeEntity;
            }

        public:
            Demo() : Game()
            {

            }

            ~Demo() override {

            }

            virtual void initialize() override {
                Game::initialize();

                prepareAssets();

                _world = new World();
                WorldLayer* mainLayer = new WorldLayer(PAX_WORLDLAYERNAME_MAIN, 3);


                EntityComponentService& es = Services::GetEntityComponentService();
                Entity* cam = new Entity();
                {
                    std::shared_ptr<PerspectiveProjection> proj = std::make_shared<PerspectiveProjection>();
                    proj->setFOV(120);
                    cam->add(es.create<Camera>(Services::GetFactory().create<Viewport>(), proj));
                    cam->add(es.create<NoClipControls>());
                    mainLayer->spawn(cam);
                }
                Entity* cube1 = createCube(redShader);
                Entity* cube2 = createCube(texShader);
                Entity* tree  = createFromFile("mesh/lowpolytree/lowpolytree.obj", simpleMatShader);
                Entity* tank  = createFromFile("mesh/ltp/LTP.obj", simpleMatShader);
                mainLayer->spawn(cube1);
                mainLayer->spawn(cube2);
                mainLayer->spawn(tree);
                mainLayer->spawn(tank);

                cam->getTransform().position()   = {0, 0,  0};
                cube1->getTransform().position() = {0, 0,  2};
                cube2->getTransform().position() = {0, 0, -2};
                tree->getTransform().position()  = {-3, 0, -5};

                tank->getTransform().position() = {1, -2, -5};

                _world->addLayer(mainLayer);
                setActiveWorld(_world);
            }
        };
    }
}

#endif //PAXENGINE3_PLAYGROUNDDEMO_H
