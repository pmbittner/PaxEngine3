//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PAXTILEDEMO_H
#define PAXENGINE3_PAXTILEDEMO_H

#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/io/event/KeyPressedEvent.h>

#include "polypropylene/log/Log.h"

#include <paxcore/gameentity/GameEntity.h>
#include <paxcore/gameentity/property/behaviours/NoClipControls.h>

#include <paxcore/rendering/graphics/SceneGraphGraphics.h>
#include <paxcore/rendering/geometry/ScreenFillingQuad.h>

#include <paxcore/rendering/factory/ViewportFactory.h>

namespace PAX {
    namespace RayMarcher {
        class Renderer : public Renderable {
            float globalGameTime = 0;

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
                shader->setUniform("gameTime", shadowSharpness);

                float dt = renderOptions.getActualDeltaTime();
                globalGameTime += dt;
                shader->setUniform("gameTime", globalGameTime);
                shader->setUniform("gameTimeDelta", renderOptions.getActualDeltaTime());

                screen->render(renderOptions);
            }
        };

        class Demo : public Game {
            World * world;
            Settings settings;

            std::shared_ptr<Shader> rayMarchingShader;
            Renderer renderer;
            GameEntity screenGameEntity, cameraGameEntity;

            void createScreen() {
                Path vert = settings.get<Path>("vertfile");
                Path frag = settings.get<Path>("fragfile");

                rayMarchingShader = Services::GetResources().loadOrGet<Shader>(Shader::FileInfo(vert, frag));

                renderer.screen = PAX::CreateScreenFillingQuad();
                renderer.screen->upload();

                SceneGraphGraphics * g = new SceneGraphGraphics();
                g->setShader(rayMarchingShader);
                g->getSceneGraph().addChild(&renderer);

                screenGameEntity.add(g);
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

                settings.parse(Services::GetPaths().getResourcePath() + "RayMarcher/raymarcher.paxconfig");

                createScreen();

                Camera * camera = new Camera(
                        Services::GetFactoryService().get<ViewportFactory>()->create(),
                        std::make_shared<Projection>()
                );
                camera->setSyncProjectionResolutionToViewportResolution(true);
                NoClipControls * noClipControls = new NoClipControls();
                noClipControls->setSpeed(0.3);
                noClipControls->setMouseSensivity(0.3);
                cameraGameEntity.add(camera);
                cameraGameEntity.add(noClipControls);
                cameraGameEntity.getTransformation().position() = settings.get<glm::vec3>("camerapos");

                WorldLayer * mainLayer = new WorldLayer("ScreenLayer", 2);
                mainLayer->spawn(&screenGameEntity);
                mainLayer->spawn(&cameraGameEntity);

                world = new World();
                world->addLayer(mainLayer);
                setActiveWorld(world);
            }
        };
    }
}

#endif //PAXENGINE3_PAXTILEDEMO_H
