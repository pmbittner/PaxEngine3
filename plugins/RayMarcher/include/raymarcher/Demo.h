//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PAXTILEDEMO_H
#define PAXENGINE3_PAXTILEDEMO_H

#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/io/event/KeyPressedEvent.h>

#include "paxutil/log/Log.h"

#include <paxcore/entity/Entity.h>
#include <paxcore/entity/property/behaviours/NoClipControls.h>

#include <paxcore/rendering/graphics/SceneGraphGraphics.h>
#include <paxcore/rendering/geometry/ScreenFillingQuad.h>

#include <paxcore/rendering/factory/ViewportFactory.h>

namespace PAX {
    namespace RayMarcher {
        class Renderer : public Renderable {
        public:
            std::shared_ptr<Mesh> screen = nullptr;
            float shadowSharpness = 1;

            ~Renderer() override = default;

            void render(RenderOptions &renderOptions) override {
                Shader * shader = renderOptions.getShaderOptions().getShader();
                glm::vec2 resolution = renderOptions.getCamera()->getProjection()->getResolution();

                shader->setUniform("resolution", resolution);
                shader->setUniform("camera", glm::inverse(renderOptions.getViewMatrix()), false);

                shader->setUniform("shadowSharpness", shadowSharpness);

                screen->render(renderOptions);
            }
        };

        class Demo : public Game {
            World * world;

            std::shared_ptr<Shader> rayMarchingShader;
            Renderer renderer;
            Entity screenEntity, cameraEntity;

            void createScreen() {
                rayMarchingShader = Services::GetResources().loadOrGet<Shader>(Shader::FileInfo(
                        Services::GetPaths().getResourcePath() + "RayMarcher/vert.glsl",
                        Services::GetPaths().getResourcePath() + "RayMarcher/frag.glsl"
                        ));

                renderer.screen = PAX::CreateScreenFillingQuad();
                renderer.screen->upload();

                SceneGraphGraphics * g = new SceneGraphGraphics();
                g->setShader(rayMarchingShader);
                g->getSceneGraph().addChild(&renderer);

                screenEntity.add(g);
            }

        public:
            void onKeyDown(KeyPressedEvent & keyPressedEvent) {
                if (keyPressedEvent.button == PAX::Key::ESCAPE)
                    Engine::Instance().stop();

                else if (keyPressedEvent.button == PAX::Key::UP) {
                    renderer.shadowSharpness += 0.05f;
                }

                else if (keyPressedEvent.button == PAX::Key::DOWN) {
                    renderer.shadowSharpness -= 0.05f;
                }
            }

            void initialize() override {
                Game::initialize();
                Services::GetEventService().add<KeyPressedEvent, Demo, &Demo::onKeyDown>(this);

                createScreen();

                Camera * camera = new Camera(
                        Services::GetFactoryService().get<ViewportFactory>()->create(),
                        std::make_shared<Projection>()
                );
                camera->setSyncProjectionResolutionToViewportResolution(true);
                NoClipControls * noClipControls = new NoClipControls();
                noClipControls->setSpeed(0.3);
                noClipControls->setMouseSensivity(0.3);
                cameraEntity.add(camera);
                cameraEntity.add(noClipControls);
                cameraEntity.getTransformation().position() = {0, 0, 2};

                WorldLayer * mainLayer = new WorldLayer("ScreenLayer", 2);
                mainLayer->spawn(&screenEntity);
                mainLayer->spawn(&cameraEntity);

                world = new World();
                world->addLayer(mainLayer);
                setActiveWorld(world);
            }
        };
    }
}

#endif //PAXENGINE3_PAXTILEDEMO_H
