//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_SDLOPENGLENGINEPLUGIN_H
#define PAXENGINE3_SDLOPENGLENGINEPLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>
#include <paxcore/io/Window.h>
#include <paxcore/service/FactoryService.h>
#include <paxcore/io/WindowFactory.h>
#include <paxcore/rendering/loader/NullTextureLoader.h>
#include "SDLOpenGLWindow.h"
#include "SDLOpenGLRenderPass.h"

#include "paxopengl/rendernodes/OpenGLContext.h"

/// Dependencies
#include "paxsdl/SDLPlugin.h"
#include "paxopengl/OpenGLEnginePlugin.h"

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            class SDLOpenGLPlugin : public EnginePlugin {
                class SDLOpenGLWindowFactory : public WindowFactory {
                    std::shared_ptr<Window> create(const char* title, int resX, int resY) override;
                } windowFactory;

            public:
                SDLOpenGLPlugin();

                void postInitialize(Engine& engine) override;
                void registerResourceLoaders(Resources& resources) override;
                void registerFactories(FactoryService &factoryService) override;
                void checkDependencies(const std::vector<EnginePlugin*> & plugins) const override;
            };
        }
    }
}

#endif //PAXENGINE3_SDLOPENGLENGINEPLUGIN_H
