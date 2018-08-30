//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_SDLOPENGLENGINEPLUGIN_H
#define PAXENGINE3_SDLOPENGLENGINEPLUGIN_H

#include <core/EnginePlugin.h>
#include <core/io/Window.h>
#include <core/service/FactoryService.h>
#include <utility/io/CSVSettingsLoader.h>
#include "SDLOpenGLWindow.h"
#include "SDLImageOpenGLTextureLoader.h"
#include "SDLOpenGLRenderPass.h"

#include "../../../opengl/include/rendernodes/OpenGLRenderPass.h"

/// Dependencies
#include "../SDLEnginePlugin.h"
#include "../../../opengl/include/OpenGLEnginePlugin.h"

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            class SDLOpenGLEnginePlugin : public EnginePlugin {
                class SDLOpenGLWindowFactory : public Factory<Window, const char*, int, int> {
                    virtual std::shared_ptr<Window> create(const char* title, int resX, int resY) {
                        std::shared_ptr<SDLOpenGLWindow> window = std::make_shared<SDLOpenGLWindow>();
                        std::string t(title);
                        window->create(t, resX, resY);
                        return window;
                    }
                } windowFactory;

            public:
                SDLOpenGLEnginePlugin() :
                EnginePlugin(
                        new EnginePluginTypedDependencies<PAX::SDL::SDLEnginePlugin, PAX::OpenGL::OpenGLEnginePlugin>("SDLOpenGLEnginePlugin")
                                )
                {

                }

                virtual void initialize(Engine& engine) override {}

                virtual void postInitialize(Engine& engine) {
                    LOG(INFO) << "[SDLOpenGLEnginePlugin::postInitialize]";
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
                    LOG(INFO) << "[SDLOpenGLEnginePlugin::postInitialize] Done";
                }

                virtual void registerResourceLoaders(Resources& resources) override {
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

                    LOG(INFO) << "SDLOpenGLEnginePlugin: Register TextureLoader (" << loaderName << ")";
                }

                virtual void registerFactories(FactoryService &factoryService) override {
                    factoryService.registerFactory(&windowFactory);
                }
            };
        }
    }
}

#endif //PAXENGINE3_SDLOPENGLENGINEPLUGIN_H
