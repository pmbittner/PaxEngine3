//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PLAYGROUNDDEMO_H
#define PAXENGINE3_PLAYGROUNDDEMO_H

#include <core/Game.h>

#include <core/rendering/camera/Camera.h>
#include <utility/rendering/Cube.h>
#include <core/rendering/graphics/SceneGraphGraphics.h>
#include <core/rendering/graphics/nodes/MeshNode.h>
#include <core/rendering/graphics/nodes/TexturingNode.h>
#include <core/rendering/data/Texture.h>
#include <core/entity/component/behaviours/NoClipControls.h>

namespace PAX {
    namespace PlaygroundDemo {
        class Demo : public Game {
            World *_world;
            std::shared_ptr<Shader> texShader;
            std::shared_ptr<Mesh> cube;

            void prepareAssets() {
                texShader = Services::GetResources().loadOrGet<Shader>(
                        Services::GetPaths().getAbsoluteResourcePath() + "shader/test/PlainTexture.vert",
                        Services::GetPaths().getAbsoluteResourcePath() + "shader/test/PlainTexture.frag"
                );
                texShader->upload();

                cube = Util::createCube(true /*with tex coords*/);
                cube->finalize();
                cube->upload();
            }

            Entity* createCube() {
                Entity* cubeEntity = new Entity();
                EntityComponentService& es = Services::GetEntityComponentService();

                std::shared_ptr<Texture> texture = Services::GetResources().loadOrGet<Texture>(
                        Services::GetPaths().getAbsoluteResourcePath() + "img/PaxEngine3_128.png"
                );
                // TODO: Make this easier
                SceneGraphGraphics* g = es.create<SceneGraphGraphics>();
                MeshNode* cubeMeshNode = new MeshNode(cube);
                cubeMeshNode->cacheUniformsFor(texShader);
                //*
                TexturingNode* texNode = new TexturingNode(texture);
                texNode->addChild(cubeMeshNode);
                g->getSceneGraph().addChild(texNode);
                /*/
                g->getSceneGraph().addChild(cubeMeshNode);
                //*/

                g->setShader(texShader);

                cubeEntity->add(g);

                return cubeEntity;
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

                //std::shared_ptr<Mesh> tree = Services::GetResources().load<Mesh>(
                //        Services::GetPaths().getAbsoluteResourcePath() + "mesh/lowpolytree.obj"
                //        );

                EntityComponentService& es = Services::GetEntityComponentService();
                Entity* cam = new Entity();
                {
                    cam->add(
                            es.create<Camera>(
                                    Services::GetFactory().create<Viewport>(),
                                            std::make_shared<PerspectiveProjection>()
                                                    ));
                    cam->add(es.create<NoClipControls>());
                    mainLayer->spawn(cam);
                }
                Entity* cube1 = createCube();
                Entity* cube2 = createCube();
                mainLayer->spawn(cube1);
                mainLayer->spawn(cube2);

                cam->getTransform().position()   = {0, 0,  0};
                cube1->getTransform().position() = {0, 0,  2};
                cube2->getTransform().position() = {0, 0, -2};

                _world->addLayer(mainLayer);
                setActiveWorld(_world);
            }
        };
    }
}

#endif //PAXENGINE3_PLAYGROUNDDEMO_H
