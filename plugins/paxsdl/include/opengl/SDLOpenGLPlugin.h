//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_SDLOPENGLENGINEPLUGIN_H
#define PAXENGINE3_SDLOPENGLENGINEPLUGIN_H

#include <paxcore/EnginePlugin.h>
#include <paxcore/io/Window.h>
#include <paxcore/service/FactoryService.h>
#include <paxcore/io/WindowFactory.h>
#include "SDLOpenGLWindow.h"
#include "SDLImageOpenGLTextureLoader.h"
#include "SDLOpenGLRenderPass.h"

#include "../../../paxopengl/include/rendernodes/OpenGLRenderPass.h"

/// Dependencies
#include "paxsdl/include/SDLPlugin.h"
#include "../../../paxopengl/include/OpenGLEnginePlugin.h"

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            class SDLOpenGLPlugin : public EnginePlugin {
                class SDLOpenGLWindowFactory : public WindowFactory {
                    std::shared_ptr<Window> create(const char* title, int resX, int resY) override {
                        std::shared_ptr<SDLOpenGLWindow> window = std::make_shared<SDLOpenGLWindow>();
                        std::string t(title);
                        window->create(t, resX, resY);
                        return window;
                    }
                } windowFactory;

            public:
                SDLOpenGLPlugin() :
                EnginePlugin(
                        new EnginePluginTypedDependencies<PAX::SDL::SDLPlugin, PAX::OpenGL::OpenGLEnginePlugin>("SDLOpenGLPlugin")
                                )
                {

                }

                void initialize(Engine& engine) override {}

                void postInitialize(Engine& engine) override {
                    LOG(INFO) << "[SDLOpenGLPlugin::postInitialize]";
                    auto *sdl    = new PAX::SDL::OpenGL::SDLOpenGLRenderPass();
                    auto *opengl = new PAX::OpenGL::OpenGLRenderPass();
                    sdl->addChild(opengl);

                    Renderer &renderer = Engine::Instance().getRenderer();

                    renderer.setSceneGraphRoot(sdl);
                    renderer.setSceneGraphGenerationEntryPoint(opengl);

                    LOG(INFO) << "\tinitialize SDLOpenGLRenderPass";
                    sdl->initialize();
                    LOG(INFO) << "\tinit OpenGL";
                    opengl->initialize();
                    LOG(INFO) << "[SDLOpenGLPlugin::postInitialize] Done";
                }

                void registerResourceLoaders(Resources& resources) override {
                    std::string loaderName;

#ifdef PAX_WITH_FREEIMAGE
#define PAX_IMAGE_LOADER_FOUND
                    loaderName = "FreeImageOpenGLTextureLoader";
                    Services::GetResources().registerLoader<Texture>(new PAX::OpenGL::FreeImageOpenGLTextureLoader());
#endif

#ifdef PAX_WITH_SDLIMAGE
#define PAX_IMAGE_LOADER_FOUND
                    loaderName = "SDLImageOpenGLTextureLoader";
                    Services::GetResources().registerLoader<Texture>(new PAX::OpenGL::SDLImageOpenGLTextureLoader());
#endif

#ifndef PAX_IMAGE_LOADER_FOUND
                    LOG(WARNING) << "    SDLOpenGLEnginePlugin: No real image loader in use (default is used)!";
                    Services::GetResources().registerLoader<Texture>(new PAX::OpenGL::NullOpenGLTextureLoader());
#endif

                    LOG(INFO) << "SDLOpenGLPlugin: Register TextureLoader (" << loaderName << ")";
                }

                void registerFactories(FactoryService &factoryService) override {
                    factoryService.set(paxtypeid(WindowFactory), &windowFactory);
                }
            };
        }
    }
}

#endif //PAXENGINE3_SDLOPENGLENGINEPLUGIN_H
