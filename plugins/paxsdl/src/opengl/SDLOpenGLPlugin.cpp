//
// Created by Paul on 25.03.2019.
//

#include <paxsdl/opengl/SDLOpenGLPlugin.h>
#include <paxcore/Engine.h>

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            std::shared_ptr<Window> SDLOpenGLPlugin::SDLOpenGLWindowFactory::create(const char *title, int resX,
                                                                                    int resY) {
                std::shared_ptr<SDLOpenGLWindow> window = std::make_shared<SDLOpenGLWindow>();
                std::string t(title);
                window->create(t, resX, resY);
                return window;
            }

            SDLOpenGLPlugin::SDLOpenGLPlugin() : EnginePlugin() {}

            void SDLOpenGLPlugin::postInitialize(PAX::Engine &engine) {
                LOG(INFO) << "[SDLOpenGLPlugin::postInitialize]";
                auto *sdl    = new PAX::SDL::OpenGL::SDLOpenGLRenderPass();
                auto *opengl = new PAX::OpenGL::OpenGLRenderPass();
                sdl->addChild(opengl);

                Renderer & renderer = ::PAX::Engine::Instance().getRenderer();

                renderer.setSceneGraphRoot(sdl);
                renderer.setSceneGraphGenerationEntryPoint(opengl);

                LOG(INFO) << "\tinitialize SDLOpenGLRenderPass";
                sdl->initialize();
                LOG(INFO) << "\tinit OpenGL";
                opengl->initialize();
                LOG(INFO) << "[SDLOpenGLPlugin::postInitialize] Done";
            }

            void SDLOpenGLPlugin::registerResourceLoaders(PAX::Resources &resources) {
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

            void SDLOpenGLPlugin::registerFactories(PAX::FactoryService &factoryService) {
                factoryService.set(paxtypeid(WindowFactory), &windowFactory);
            }

            void SDLOpenGLPlugin::checkDependencies(const std::vector<PAX::EnginePlugin *> &plugins) const {
                static EnginePluginTypedDependencies<
                        PAX::SDL::SDLPlugin,
                        PAX::OpenGL::OpenGLEnginePlugin> dependencies("PAX::SDL::OpenGL::SDLOpenGLPlugin");
                dependencies.checkDependencies(plugins);
            }
        }
    }
}