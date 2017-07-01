//
// Created by Paul on 17.06.2017.
//

#ifndef PAXENGINE3_OPENGLDEMO_H
#define PAXENGINE3_OPENGLDEMO_H

#include <iostream>
#include "../../core/Game.h"
#include "../../test/SDLTestApplication2.h"
#include "../../sdl/opengl/SDLOpenGLWindow.h"
#include "../../opengl/OpenGLRenderPass.h"
#include "../../sdl/utitlity/Path.h"
#include "../MoveToMouseBehaviour.h"
#include "../../sdl/opengl/SDLOpenGLRenderPass.h"
#include "../../opengl/OpenGLViewport.h"
#include "Cube.h"
#include "../RotateAround3D.h"
#include "../CameraControls.h"

namespace PAX {
    namespace Demo {
        class OpenGLDemo : public Game {
            World testWorld;

        public:
            virtual void initialize() override {
                Game::initialize();

                SDLOpenGLRenderPass *sdl = new SDLOpenGLRenderPass();
                OpenGL::OpenGLRenderPass *opengl = new OpenGL::OpenGLRenderPass();
                sdl->addChild(opengl);

                Renderer &renderer = Engine::GetInstance()->getRenderer();
                renderer.setSceneGraphRoot(sdl);
                renderer.setSceneGraphGenerationEntryPoint(opengl);

                sdl->initialize();
                opengl->initialize();

                setActiveWorld(&testWorld);

                Entity *camera = new Entity();
                camera->add<Camera>(new Camera(new OpenGL::OpenGLViewport(0, 0, 400, 600)));
                camera->add<Behaviour>(new CameraControls);

                Entity *camera2 = new Entity();
                camera2->add<Camera>(new Camera(new OpenGL::OpenGLViewport(400, 0, 400, 600)));
                //camera2->add<Behaviour>(new CameraControls);

                Entity *cube = createCubeEntity();
                cube->add<Behaviour>(new RotateAround3D);
                cube->getTransform().setZ(-5);

                //*/
                testWorld.getMainLayer()->spawn(camera);
                testWorld.getMainLayer()->spawn(camera2);
                //*/
                testWorld.getMainLayer()->spawn(cube);
                //*/
            }
        };
    }
}

#endif //PAXENGINE3_OPENGLDEMO_H
