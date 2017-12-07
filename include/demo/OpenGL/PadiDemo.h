//
// Created by Paul on 17.06.2017.
//

#ifndef PAXENGINE3_PADIDEMO_H
#define PAXENGINE3_PADIDEMO_H

#include <iostream>

#include "Cube.h"
#include "../../core/Game.h"
#include "../../test/SDLTestApplication2.h"
#include "../../sdl/opengl/SDLOpenGLWindow.h"
#include "../../opengl/rendernodes/OpenGLRenderPass.h"
#include "../behaviours/MoveToMouseBehaviour.h"
#include "../../sdl/opengl/SDLOpenGLRenderPass.h"
#include "../../opengl/OpenGLViewport.h"
#include "../../opengl/OpenGLSprite.h"
#include "../../core/rendering/camera/PixelScreenProjection.h"
#include "../behaviours/Dance2D.h"
#include "../behaviours/RotateAround3D.h"
#include "../behaviours/CameraControls.h"
#include "../../utility/io/CSVSettingsLoader.h"
#include "../../core/rendering/camera/FullPixelScreenProjection.h"

namespace PAX {
    namespace Demo {
        class PadiDemo : public Game {
            World *_testWorld;

        public:
            void onEntitySpawned(EntitySpawnedEvent &event) {
                LOG(INFO) << "Demo: Entity spawned " << event.entity;
            }

            void initRendering() {
                SDL::OpenGL::SDLOpenGLRenderPass *sdl = new SDL::OpenGL::SDLOpenGLRenderPass();
                OpenGL::OpenGLRenderPass *opengl = new OpenGL::OpenGLRenderPass();
                sdl->addChild(opengl);

                Renderer &renderer = Engine::Instance().getRenderer();
                renderer.setSceneGraphRoot(sdl);
                renderer.setSceneGraphGenerationEntryPoint(opengl);

                sdl->initialize();
                opengl->initialize();
            }

            void initGui(glm::vec2 res = {800, 600}) {
                WorldLayer *guiLayer = _testWorld->getGUILayer();

                Entity *camera = new Entity();
                camera->add<Camera>(new Camera(new OpenGL::OpenGLViewport(0, 0, res.x, res.y), new FullPixelScreenProjection()));

                OpenGL::OpenGLSprite::Initialize();
                Entity *paxLogo = new Entity();
                float w = 100, h = 100;
                paxLogo->add<Graphics>(new OpenGL::OpenGLSprite(Services::GetResources().loadOrGet<Texture>((Services::GetPaths().RelativeResourcePath() + "img/PaxEngine3_128.png").c_str())));
                paxLogo->add<Behaviour>(new Dance2D());
                paxLogo->getTransform().setPosition(0, -res.y/2 + h, -1);
                paxLogo->getTransform().setScale(w, h);

                Entity* blackBar = new Entity();
                blackBar->add<Graphics>(new OpenGL::OpenGLSprite(Services::GetResources().loadOrGet<Texture>((Services::GetPaths().RelativeResourcePath() + "img/Black16.png").c_str())));
                blackBar->getTransform().setPosition(0, 0, -2);
                blackBar->getTransform().setScale(5, res.y);

                guiLayer->spawn(camera);
                guiLayer->spawn(paxLogo);
                guiLayer->spawn(blackBar);
            }

            virtual void initialize() override {
                LOG(INFO) << "Demo: Initializing";

                Window *window = Engine::Instance().getWindow();
                glm::vec2 res = window->getResolution();

                Game::initialize();
                _testWorld = new World();
                _testWorld->getEventService().add<EntitySpawnedEvent, PadiDemo, &PadiDemo::onEntitySpawned>(this);

                setActiveWorld(_testWorld);

                initRendering();
                initGui(res);

                Entity *cgCube = createCubeEntity(glm::vec3(1, 1, 1), "img/cg512borders.png");
                cgCube->add<Behaviour>(new CameraControls);
                cgCube->getTransform().setZ(3);
                cgCube->getTransform().setY(-1.0f);

                Entity *paxCube = createCubeEntity(glm::vec3(1,1,1), "img/PaxEngine3_128.png");
                paxCube->add<Behaviour>(new RotateAround3D(glm::vec3(0, 0.005, 0.005)));

                Entity *tuCube = createCubeEntity(glm::vec3(1, 1, 1), "img/tu512.png");
                tuCube->getTransform().setY(-1);
                tuCube->setParent(paxCube);

                Entity *cgCubeCamera = new Entity();
                cgCubeCamera->add<Camera>(new Camera(new OpenGL::OpenGLViewport(0, 0, res.x/2, res.y)));
                cgCubeCamera->setParent(cgCube);
                cgCubeCamera->getTransform().setY(1.3f);
                cgCubeCamera->getTransform().setZ(2.0f);

                Entity *paxCubeCamera = new Entity();
                paxCubeCamera->add<Camera>(new Camera(new OpenGL::OpenGLViewport(res.x/2, 0, res.x/2, res.y)));
                paxCubeCamera->setParent(paxCube);
                paxCubeCamera->getTransform().setRotation(0, M_PI, 0);
                paxCubeCamera->getTransform().setZ(0.6f);

                // orientation cubes
                Entity *bonuscubeLeft = createCubeEntity(glm::vec3(1, 0, 0));
                bonuscubeLeft->add<Behaviour>(new RotateAround3D(glm::vec3(0, 0, -0.005)));
                bonuscubeLeft->getTransform().setPosition(-3, 0, 0);
                _testWorld->getMainLayer()->spawn(bonuscubeLeft);

                Entity *bonuscubeRight = createCubeEntity(glm::vec3(0, 0, 1));
                bonuscubeRight->add<Behaviour>(new RotateAround3D(glm::vec3(-0.005, 0.005, 0.005)));
                bonuscubeRight->getTransform().setPosition(3, 0, 0);
                _testWorld->getMainLayer()->spawn(bonuscubeRight);

                Entity *bonuscubeBack = createCubeEntity(glm::vec3(0, 1, 0));
                bonuscubeBack->add<Behaviour>(new RotateAround3D(glm::vec3(0.005, 0, 0)));
                bonuscubeBack->getTransform().setPosition(0, 0, -3);
                _testWorld->getMainLayer()->spawn(bonuscubeBack);

                _testWorld->getMainLayer()->spawn(cgCube);
                _testWorld->getMainLayer()->spawn(paxCube);

                Util::CSVSettingsLoader graphicSettings(Services::GetPaths().RelativeResourcePath() + "config/graphics.ini", '=', true);
                window->setFullscreen(graphicSettings.getBool("fullscreen"));
            }
        };
    }
}

#endif //PAXENGINE3_PADIDEMO_H
