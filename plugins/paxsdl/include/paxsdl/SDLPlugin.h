//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_SDLENGINEPLUGIN_H
#define PAXENGINE3_SDLENGINEPLUGIN_H

#include <SDL2/SDL.h>
//#include <SDL_ttf.h>
#include <paxcore/plugin/EnginePlugin.h>
#include <paxcore/service/Paths.h>
#include <paxcore/service/Services.h>
#include <paxcore/io/InputSystemFactory.h>
#include <paxutil/log/Log.h>
#include "SDLInputSystem.h"
#include "SDLImageTextureLoader.h"

#include <paxcore/rendering/loader/NullTextureLoader.h>

namespace PAX {
    namespace SDL {
        class SDLPlugin : public EnginePlugin {
            class SDLInputSystemFactory : public InputSystemFactory {
                std::shared_ptr<InputSystem> create() override {
                    return std::make_shared<SDLInputSystem>();
                }
            } inputSystemFactory;

#ifdef PAX_WITH_SDLIMAGE
            SDLImageTextureLoader imageLoader;
#endif

        public:
            void initialize(Engine& engine) override {
                EnginePlugin::initialize(engine);

                Log::out.info() << "[SDLPlugin::initialize] initialize SDL" << std::endl;

                SDL_Init(SDL_INIT_EVERYTHING);
                //TTF_Init();
            }

            void terminate(Engine& engine) override {
                SDL_Quit();
                EnginePlugin::terminate(engine);
            }

            void registerFactories(FactoryService& factoryService) override {
                factoryService.set(paxtypeid(InputSystemFactory), &inputSystemFactory);
            }

            void registerResourceLoaders(Resources& resources) override {
#ifdef PAX_WITH_SDLIMAGE
                Services::GetResources().registerLoader<Texture>(&imageLoader);
#endif
            }
        };
    }
}

#endif //PAXENGINE3_SDLENGINEPLUGIN_H
