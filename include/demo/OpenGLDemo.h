//
// Created by Paul on 17.06.2017.
//

#ifndef PAXENGINE3_OPENGLDEMO_H
#define PAXENGINE3_OPENGLDEMO_H

#include <iostream>
#include "../core/Game.h"
#include "../test/SDLTestApplication2.h"
#include "../sdl/opengl/SDLOpenGLWindow.h"
#include "../opengl/OpenGLRenderPass.h"
#include "../sdl/utitlity/Path.h"
#include "MoveToMouseBehaviour.h"
#include "../sdl/opengl/SDLOpenGLRenderPass.h"
#include "../opengl/OpenGLViewport.h"

namespace PAX {
    namespace Demo {
        class OpenGLDemo : public Game {
            World testWorld;
            Entity testEntity;

        public:
            virtual void initialize() override {
                Game::initialize();

                SDLOpenGLRenderPass *sdl = new SDLOpenGLRenderPass();
                OpenGLRenderPass *opengl = new OpenGLRenderPass();
                sdl->addChild(opengl);

                Renderer &renderer = Engine::GetInstance()->getRenderer();
                renderer.setSceneGraphRoot(sdl);
                renderer.setSceneGraphGenerationEntryPoint(opengl);

                sdl->initialize();
                opengl->initialize();

                setActiveWorld(&testWorld);

                //SDLSprite *sprite = new SDLSprite(renderpass->getSDLRenderer(), getResourcePath() + "img/test/Gilgamesh.bmp");

                //testEntity.add<Graphics>(sprite);
                testEntity.add<Camera>(new Camera(new OpenGLViewport(0, 0, 100, 100)));
                testEntity.add<Behaviour>(new MoveToMouseBehaviour);

                testEntity.getTransform().setPosition(300, 200);

                testWorld.getMainLayer()->spawn(&testEntity);
                //*/
            }
        };
    }
}

#endif //PAXENGINE3_OPENGLDEMO_H
