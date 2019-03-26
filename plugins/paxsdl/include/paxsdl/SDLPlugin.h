//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_SDLENGINEPLUGIN_H
#define PAXENGINE3_SDLENGINEPLUGIN_H

#include <SDL2/SDL.h>
//#include <SDL_ttf.h>
#include <paxcore/EnginePlugin.h>
#include <paxcore/service/Paths.h>
#include <paxcore/service/Services.h>
#include <paxcore/io/InputSystemFactory.h>
#include "SDLInputSystem.h"

namespace PAX {
    namespace SDL {
        class SDLPlugin : public EnginePlugin {
            class SDLInputSystemFactory : public InputSystemFactory {
                std::shared_ptr<InputSystem> create() override {
                    return std::make_shared<SDLInputSystem>();
                }
            } inputSystemFactory;

        public:
            void initialize(Engine& engine) override {
                EnginePlugin::initialize(engine);

                LOG(INFO) << "initialize SDL";

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
        };
    }
}

#endif //PAXENGINE3_SDLENGINEPLUGIN_H
