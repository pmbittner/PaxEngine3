//
// Created by Paul on 17.06.2017.
//

#ifndef PAXENGINE3_OPENGLDEMO_H
#define PAXENGINE3_OPENGLDEMO_H

#include <iostream>

#include "Cube.h"
#include "../../core/Game.h"
#include "../../test/SDLTestApplication2.h"
#include "../../sdl/opengl/SDLOpenGLWindow.h"
#include "../../opengl/rendernodes/OpenGLRenderPass.h"
#include "../../sdl/utitlity/Path.h"
#include "../MoveToMouseBehaviour.h"
#include "../../sdl/opengl/SDLOpenGLRenderPass.h"
#include "../../opengl/OpenGLViewport.h"
#include "../../opengl/OpenGLSprite.h"
#include "../../core/rendering/camera/PixelScreenProjection.h"
#include "../Dance2D.h"
#include "../RotateAround3D.h"
#include "../CameraControls.h"

namespace PAX {
    namespace Demo {
        class OpenGLDemo : public Game {
            World *_testWorld;

        public:
            void onEntitySpawned(EntitySpawnedEvent &event) {
                LOG(INFO) << "Demo: Entity spawned " << event.entity->getName();
            }

            void initRendering() {
                SDL::OpenGL::SDLOpenGLRenderPass *sdl = new SDL::OpenGL::SDLOpenGLRenderPass();
                OpenGL::OpenGLRenderPass *opengl = new OpenGL::OpenGLRenderPass();
                sdl->addChild(opengl);

                Renderer &renderer = Engine::GetInstance()->getRenderer();
                renderer.setSceneGraphRoot(sdl);
                renderer.setSceneGraphGenerationEntryPoint(opengl);

                sdl->initialize();
                opengl->initialize();
            }

            void initGui() {
                WorldLayer *guiLayer = _testWorld->getGUILayer();

                Entity *camera = new Entity();
                camera->add<Camera>(new Camera(new OpenGL::OpenGLViewport(0, 0, 800, 600), new PixelScreenProjection()));

                OpenGL::OpenGLSprite::Initialize();
                Entity *paxLogo = new Entity("DemoGuiElement");
                float w = 100, h = 100;
                paxLogo->add<Graphics>(new OpenGL::OpenGLSprite(new OpenGL::OpenGLTexture2D(getResourcePath() + "img/PaxEngine3_128.png")));
                paxLogo->add<Behaviour>(new Dance2D());
                paxLogo->getTransform().setPosition(0, -300 + h, -1);
                paxLogo->getTransform().setScale(w, h);

                Entity* blackBar = new Entity("SplitScreenDivider");
                blackBar->add<Graphics>(new OpenGL::OpenGLSprite(new OpenGL::OpenGLTexture2D(getResourcePath() + "img/Black16.png")));
                blackBar->getTransform().setPosition(0, 0, -2);
                blackBar->getTransform().setScale(5, 610);

                guiLayer->spawn(camera);
                guiLayer->spawn(paxLogo);
                guiLayer->spawn(blackBar);
            }

            virtual void initialize() override {
                LOG(INFO) << "Demo: Initializing";

                Game::initialize();
                _testWorld = new World();
                _testWorld->getEventService().add<EntitySpawnedEvent, OpenGLDemo, &OpenGLDemo::onEntitySpawned>(this);

                setActiveWorld(_testWorld);

                initRendering();
                initGui();

                Entity *cgCube = createCubeEntity(glm::vec3(1, 1, 1), "img/cg512borders.png");
                cgCube->add<Behaviour>(new CameraControls);
                cgCube->getTransform().setZ(3);
                cgCube->getTransform().setY(-1.0f);

                Entity *paxCube = createCubeEntity(glm::vec3(1,1,1), "img/PaxEngine3_128.png");
                paxCube->add<Behaviour>(new RotateAround3D(glm::vec3(0, 0.005, 0.005)));

                Entity *tuCube = createCubeEntity(glm::vec3(1, 1, 1), "img/tu512.png");
                tuCube->getTransform().setY(-1);
                tuCube->setParent(paxCube);

                Entity *cgCubeCamera = new Entity("PaxCubeCam");
                cgCubeCamera->add<Camera>(new Camera(new OpenGL::OpenGLViewport(0, 0, 400, 600)));
                cgCubeCamera->setParent(cgCube);
                cgCubeCamera->getTransform().setY(1.3f);
                cgCubeCamera->getTransform().setZ(2.0f);

                Entity *paxCubeCamera = new Entity("CgCubeCam");
                paxCubeCamera->add<Camera>(new Camera(new OpenGL::OpenGLViewport(400, 0, 400, 600)));
                paxCubeCamera->setParent(paxCube);
                paxCubeCamera->getTransform().setRotation(0, M_PI, 0);
                paxCubeCamera->getTransform().setZ(0.6f);

                _testWorld->getMainLayer()->spawn(cgCube);
                _testWorld->getMainLayer()->spawn(paxCube);
            }
        };
    }
}

#endif //PAXENGINE3_OPENGLDEMO_H
