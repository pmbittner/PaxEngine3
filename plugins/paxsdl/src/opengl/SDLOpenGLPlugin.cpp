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
                Log::out.info() << "[SDLOpenGLPlugin::postInitialize]" << std::endl;
                auto *sdl    = new PAX::SDL::OpenGL::SDLOpenGLContext();
                auto *opengl = new PAX::OpenGL::OpenGLContext();
                sdl->addChild(opengl);

                Renderer & renderer = ::PAX::Engine::Instance().getRenderer();

                renderer.setSceneGraphRoot(sdl);
                renderer.setSceneGraphGenerationEntryPoint(opengl);

                Log::out.info() << "\tinitialize SDLOpenGLContext" << std::endl;
                sdl->initialize();
                Log::out.info() << "\tinit OpenGL" << std::endl;
                opengl->initialize();
                Log::out.info() << "[SDLOpenGLPlugin::postInitialize] Done" << std::endl;
            }

            void SDLOpenGLPlugin::registerResourceLoaders(PAX::Resources &resources) {
                std::string loaderName;
            }

            void SDLOpenGLPlugin::registerFactories(PAX::FactoryService &factoryService) {
                factoryService.set(paxtypeid(WindowFactory), &windowFactory);
            }

            void SDLOpenGLPlugin::checkDependencies(const std::vector<PAX::EnginePlugin *> &plugins) const {
                static EnginePluginTypedDependencies<PAX::SDL::SDLPlugin, PAX::OpenGL::OpenGLPlugin>
                        dependencies("PAX::SDL::OpenGL::SDLOpenGLPlugin");
                dependencies.checkDependencies(plugins);
            }
        }
    }
}